#pragma once

#include <astra/astra.hpp>
#include "body_tracker.hpp"
#include "../../../objects/world.hpp"

struct AstraWrapper
{
public:
	AstraWrapper(astra::DepthStream & depthStream, astra::BodyStream & bodyStream, astra::SkeletonProfile & profile, 
		astra::BodyTrackingFeatureFlags & features, BodyTracker & listener, World & world);

	void processEvents();
	void update();
	void render();

private:
	astra::DepthStream& depthStream; 
	astra::BodyStream& bodyStream;
	astra::SkeletonProfile& profile;
	astra::BodyTrackingFeatureFlags& features;
	World& world;
	BodyTracker& listener;
};