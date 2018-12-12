/*
 * Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// own
#include "WindowQuad.h"
#include "common.h"

// kwineffects
#include <kwineffects.h>

/**
 *
 **/
class Model {
public:
    struct Parameters {
        std::chrono::milliseconds squashDuration;
        std::chrono::milliseconds stretchDuration;
        std::chrono::milliseconds bumpDuration;
        QEasingCurve shapeCurve;
        qreal shapeFactor;
        int bumpDistance;
    };

    explicit Model(KWin::EffectWindow* window = nullptr);

    /**
     * This enum type is used to specify kind of the current animation.
     **/
    enum class AnimationKind {
        Minimize,
        Unminimize
    };

    /**
     *
     **/
    void start(AnimationKind kind);

    /**
     *
     **/
    void step(std::chrono::milliseconds delta);

    /**
     * Returns whether the animation is complete.
     **/
    bool done() const;

    /**
     *
     **/
    void apply(QVector<WindowQuad>& quads) const;

    /**
     *
     **/
    Parameters parameters() const;

    /**
     *
     **/
    void setParameters(const Parameters& parameters);

    /**
     *
     **/
    KWin::EffectWindow* window() const;

    /**
     *
     **/
    void setWindow(KWin::EffectWindow* window);

    /**
     *
     **/
    bool needsClip() const;

    /**
     *
     **/
    QRegion clipRegion() const;

private:
    void applyBump(QVector<WindowQuad>& quads) const;
    void applyStretch1(QVector<WindowQuad>& quads) const;
    void applyStretch2(QVector<WindowQuad>& quads) const;
    void applySquash(QVector<WindowQuad>& quads) const;

    void updateMinimizeStage();
    void updateUnminimizeStage();

    Direction findDirectionToIcon() const;
    int computeBumpDistance() const;
    qreal computeShapeFactor() const;

    Parameters m_parameters;

    enum class AnimationStage {
        Bump,
        Stretch1,
        Stretch2,
        Squash
    };

    KWin::EffectWindow* m_window;
    AnimationKind m_kind;
    AnimationStage m_stage;
    KWin::TimeLine m_timeLine;
    Direction m_direction;
    int m_bumpDistance;
    qreal m_shapeFactor;
    bool m_clip;
    bool m_done = false;
};