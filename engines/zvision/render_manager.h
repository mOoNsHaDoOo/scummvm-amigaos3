/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ZVISION_RENDER_MANAGER_H
#define ZVISION_RENDER_MANAGER_H

#include "common/types.h"
#include "common/rect.h"

#include "zvision/render_table.h"

class OSystem;

namespace Common {
class String;
class SeekableReadStream;
}

namespace Video {
class VideoDecoder;
}

namespace ZVision {

class RenderManager {
public:
	RenderManager(OSystem *system, const Common::Rect workingWindow);
	~RenderManager();

private:
	OSystem *_system;
	const int _workingWidth;
	const int _workingHeight;
	const Common::Rect _workingWindow;
	RenderTable _renderTable;

	Common::SeekableReadStream *_currentBackground;
	Common::Point _backgroundOffset;
	uint16 _backgroundWidth;
	uint16 _backgroundHeight;

	int _backgroundInverseVelocity;
	uint _accumulatedVelocityMilliseconds;

	byte *_scaledVideoFrameBuffer;

public:
	void initialize();
	void update(uint deltaTimeInMillis);

	/**
	 * Blits the image or a portion of the image to the screen. Actual screen updates won't happen until the end of the frame.
	 * The image will be clipped to fit inside the working window. Coords are in working window space, not screen space!
	 *
	 * @param fileName        Name of the image file
	 * @param destinationX    X position where the image should be put. Coords are in working window space, not screen space!
	 * @param destinationY    Y position where the image should be put. Coords are in working window space, not screen space!
	 * @param subRectangle    The subrectangle of the image that should be rendered. If this is an empty rectangle, it will blit the entire image. Coords are in working window space, not screen space!
	 */
	void renderImageToScreen(const Common::String &fileName, uint32 destinationX, uint32 destinationY, Common::Rect subRectangle = Common::Rect(0, 0, 0, 0), bool wrap = false);

	/**
	 * Blits the image or a portion of the image to the screen. Actual screen updates won't happen until the end of the frame.
	 * The image will be clipped to fit inside the working window. Coords are in working window space, not screen space!
	 *
	 * @param stream          Stream to read the image data from
	 * @param destinationX    X position where the image should be put. Coords are in working window space, not screen space!
	 * @param destinationY    Y position where the image should be put. Coords are in working window space, not screen space!
	 * @param subRectangle    The subrectangle of the image that should be rendered. If this is an empty rectangle, it will blit the entire image. Coords are in working window space, not screen space!
	 */
	void renderImageToScreen(Common::SeekableReadStream &stream, uint32 destinationX, uint32 destinationY, Common::Rect subRectangle = Common::Rect(0, 0, 0, 0), bool wrap = false);

	/**
	 * Sets the current background image to be used by the RenderManager and immediately
	 * blits it to the screen. (It won't show up until the end of the frame)
	 *
	 * @param fileName    The name of the image file
	 */
	void setBackgroundImage(const Common::String &fileName);

	void setBackgroundPosition(int offset);
	
	void setBackgroundVelocity(int velocity);

	const Common::Point screenSpaceToImageSpace(const Common::Point &point);

	RenderTable *getRenderTable();

private:
	void renderSubRectToScreen(uint16 *buffer, uint32 imageWidth, uint32 imageHeight, uint32 horizontalPitch, uint32 destinationX, uint32 destinationY, Common::Rect subRectangle, bool wrap);

	void moveBackground(int offset);
};

} // End of namespace ZVision

#endif
