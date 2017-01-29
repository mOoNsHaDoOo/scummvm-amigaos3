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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TITANIC_MUSIC_ROOM_H
#define TITANIC_MUSIC_ROOM_H

#include "common/array.h"
#include "titanic/sound/music_room_handler.h"

namespace Titanic {

class CGameManager;
class CSound;

class CMusicRoom {
	struct Controls {
		int _speedControl;
		int _pitchControl;
		int _directionControl;
		int _inversionControl;
		int _muteControl;

		Controls() : _speedControl(0), _pitchControl(0), _directionControl(0),
			_inversionControl(0), _muteControl(0) {}
	};
private:
	Common::Array<Controls> _controls;
public:
	static CMusicRoomHandler *_musicHandler;
public:
	CGameManager *_gameManager;
	CSound *_sound;
public:
	CMusicRoom(CGameManager *owner);
	~CMusicRoom();

	/**
	 * Creates a music handler
	 */
	CMusicRoomHandler *createMusicHandler();

	/**
	 * Destroys and currently active music handler
	 */
	void destroyMusicHandler();

	/**
	 * Sets the speed control for a given instrument
	 */
	void setSpeedControl(MusicInstrument instrument, int val) { _controls[instrument]._speedControl = val; }

	/**
	 * Sets the pitch control for a given instrument
	 */
	void setPitchControl(MusicInstrument instrument, int val) { _controls[instrument]._pitchControl = val; }

	/**
	 * Sets the direction control for a given instrument
	 */
	void setDirectionControl(MusicInstrument instrument, int val) { _controls[instrument]._directionControl = val; }

	/**
	 * Sets the inversion control for a given instrument
	 */
	void setInversionControl(MusicInstrument instrument, int val) { _controls[instrument]._inversionControl = val; }

	/**
	 * Sets the mute control for a given instrument
	 */
	void setMuteControl(MusicInstrument instrument, int val) { _controls[instrument]._muteControl = val; }

	/**
	 * Sets up the music controls
	 */
	void setupMusic(int volume);

	/**
	 * Stop playing music
	 */
	void stopMusic();
};

} // End of namespace Titanic

#endif /* TITANIC_MUSIC_ROOM_H */
