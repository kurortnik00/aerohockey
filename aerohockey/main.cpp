#include <cstdio>
#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <astra/astra.hpp>

#include "control/orbbec/astra/astra_wrapper.hpp"
#include "control/orbbec/astra/body_tracker.hpp"
#include "objects/world.hpp"
#include "states/state.hpp"
#include "states/manager.hpp"

astra::DepthStream configure_depth(astra::DepthStream & depthStream, astra::StreamReader& reader)
{
	//We don't have to set the mode to start the stream, but if you want to here is how:
	astra::ImageStreamMode depthMode;

	depthMode.set_width(640);
	depthMode.set_height(480);
	depthMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
	depthMode.set_fps(30);

	depthStream.set_mode(depthMode);

	return depthStream;
}

int main()
{
	astra::initialize();

	// TODO: obtain license key
	const char* licenseString = "<INSERT LICENSE KEY HERE>";
	orbbec_body_tracking_set_license(licenseString);

	astra::StreamSet sensor;
	astra::StreamReader reader = sensor.create_reader();

	astra::DepthStream depthStream = reader.stream<astra::DepthStream>();
	depthStream = configure_depth(depthStream, reader);
	depthStream.start();

	astra::BodyStream bodyStream = reader.stream<astra::BodyStream>();
	bodyStream.start();

	astra::SkeletonProfile profile = bodyStream.get_skeleton_profile();
	astra::BodyTrackingFeatureFlags features = astra::BodyTrackingFeatureFlags::Joints;

	World world(1280.f, 960.f);
	BodyTracker listener(world);
	reader.add_listener(listener);

	AstraWrapper wrapper(depthStream, bodyStream, profile, features, listener, world);
	StateManager manager(States::Type::Preparation, world, wrapper);

    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    sf::Time update_time = sf::seconds(1.f / 60.f);

    while (world.mWindow.isOpen())
    {
        manager.processEvents();
        elapsed += clock.restart();
		
		while (elapsed > update_time)
        {
            manager.processEvents();
            manager.update(update_time.asSeconds());
            elapsed -= update_time;
        }

        manager.render();
    }

	astra::terminate();

    return EXIT_SUCCESS;
}