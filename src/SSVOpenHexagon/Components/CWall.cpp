// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVOpenHexagon/Core/HexagonGame.hpp"
#include "SSVOpenHexagon/Components/CPlayer.hpp"
#include "SSVOpenHexagon/Components/CWall.hpp"
#include "SSVOpenHexagon/Utils/Utils.hpp"

using namespace sf;
using namespace ssvs;

namespace hg
{
    CWall::CWall(HexagonGame& mHexagonGame, const Vec2f& mCenterPos,
        int mSide, float mThickness, float mDistance, const SpeedData& mSpeed,
        const SpeedData& mCurve)
        :  hexagonGame(&mHexagonGame), centerPos{mCenterPos},
          speed{mSpeed}, curve{mCurve}, distance{mDistance},
          thickness{mThickness}, side{mSide}
    {
        const float div{ssvu::tau / hexagonGame->getSides() * 0.5f},
            angle{div * 2.f * side};

        vertexPositions[0] = getOrbitRad(centerPos, angle - div, distance);
        vertexPositions[1] = getOrbitRad(centerPos, angle + div, distance);
        vertexPositions[2] =
            getOrbitRad(centerPos, angle + div + hexagonGame->getWallAngleLeft(),
                distance + thickness + hexagonGame->getWallSkewLeft());
        vertexPositions[3] = getOrbitRad(centerPos,
            angle - div + hexagonGame->getWallAngleRight(),
            distance + thickness + hexagonGame->getWallSkewRight());
        removed = false;
    }

    void CWall::draw()
    {
    		if (removed) return;
        auto colorMain(hexagonGame->getColorMain());
        if(hueMod != 0) colorMain = Utils::transformHue(colorMain, hueMod);

        for(auto i(0u); i < 4; ++i)
            hexagonGame->wallQuads.emplace_back(vertexPositions[i], colorMain);
    }
    
    void CWall::update(FT mFT)
    {
        speed.update(mFT);
        curve.update(mFT);

        float radius{hexagonGame->getRadius() * 0.65f};
        int pointsOnCenter{0};

        for(auto& vp : vertexPositions)
        {
            if(std::abs(vp.x - centerPos.x) < radius &&
                std::abs(vp.y - centerPos.y) < radius)
                ++pointsOnCenter;
            else
            {
                moveTowards(vp, centerPos, speed.speed * 5.f * mFT);
                rotateRadAround(vp, centerPos, curve.speed / 60.f * mFT);
            }
        }

        if(pointsOnCenter > 3) 
        { 
            killed=true;
            removed=false;
        }
    }
}
