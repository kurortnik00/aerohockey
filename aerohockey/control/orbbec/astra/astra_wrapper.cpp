#include "astra_wrapper.hpp"

AstraWrapper::AstraWrapper(astra::DepthStream& depthStream, astra::BodyStream& bodyStream, astra::SkeletonProfile& profile,
	astra::BodyTrackingFeatureFlags& features, BodyTracker& listener, World& world)
	: depthStream (depthStream), bodyStream (bodyStream), profile (profile), features (features), listener (listener), world (world)
{

}

void AstraWrapper::processEvents()
{
	sf::Event event;
	while (world.mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			world.mWindow.close();
			break;
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::C && event.key.control)
			{
				world.mWindow.close();
			}
			switch (event.key.code)
			{
			case sf::Keyboard::D:
			{
				auto oldMode = depthStream.mode();
				astra::ImageStreamMode depthMode;

				depthMode.set_width(640);
				depthMode.set_height(400);
				depthMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
				depthMode.set_fps(30);

				depthStream.set_mode(depthMode);
				auto newMode = depthStream.mode();
				printf("Changed depth mode: %dx%d @ %d -> %dx%d @ %d\n",
					oldMode.width(), oldMode.height(), oldMode.fps(),
					newMode.width(), newMode.height(), newMode.fps());
				break;
			}
			case sf::Keyboard::Escape:
				world.mWindow.close();
				break;
			case sf::Keyboard::R:
				depthStream.enable_registration(!depthStream.registration_enabled());
				break;
			case sf::Keyboard::M:
				depthStream.enable_mirroring(!depthStream.mirroring_enabled());
				break;
			case sf::Keyboard::P:
				if (profile == astra::SkeletonProfile::Full)
				{
					profile = astra::SkeletonProfile::Basic;
					printf("Skeleton Profile: basic\n");
				}
				else
				{
					profile = astra::SkeletonProfile::Full;
					printf("Skeleton Profile: full\n");
				}
				bodyStream.set_skeleton_profile(profile);
				break;
			case sf::Keyboard::T:
				if (features == astra::BodyTrackingFeatureFlags::Segmentation)
				{
					// Joints includes Segmentation
					features = astra::BodyTrackingFeatureFlags::Joints;
					printf("Default Body Features: Seg+Body\n");
				}
				else if (features == astra::BodyTrackingFeatureFlags::Joints)
				{
					// HandPoses includes Joints and Segmentation
					features = astra::BodyTrackingFeatureFlags::HandPoses;
					printf("Default Body Features: Seg+Body+Hand\n");
				}
				else
				{
					// HandPoses includes Joints and Segmentation
					features = astra::BodyTrackingFeatureFlags::Segmentation;
					printf("Default Body Features: Seg\n");
				}
				bodyStream.set_default_body_features(features);
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}

void AstraWrapper::update()
{
	astra_update();
}

void AstraWrapper::render()
{
	listener.draw_to(world.mWindow);
}