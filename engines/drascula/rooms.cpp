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
 * $URL$
 * $Id$
 *
 */

#include "drascula/drascula.h"

namespace Drascula {

static const int mirar_t[3] = {100, 101, 54};
static const char mirar_v[3][14] = {"100.als", "101.als", "54.als"};
static const int poder_t[6] = {11, 109, 111, 110, 115, 116};
static const char poder_v[6][14] = {"11.als", "109.als", "111.als", "110.als", "115.als", "116.als"};

struct RoomTalkAction {
	int num;
	int action;
	int objectID;
	int speechID;
};

// TODO: move these elsewhere, or in a .dat file?
// Note: default action needs to be LAST for each group
// of actions with the same number
RoomTalkAction room0Actions[] = {
	// num	action		object	speech
	{ 1,	kVerbLook,		-1,		 54 },
	{ 1,	kVerbMove,		-1,		 19 },
	{ 1,	kVerbPick,		-1,		 11 },
	{ 1,	kVerbOpen,		-1,		  9 },
	{ 1,	kVerbClose,		-1,		  9 },
	{ 1,	kVerbTalk,		-1,		 16 },
	{ 1,	kVerbDefault,	-1,		 11 },
	// -------------------------------
	{ 2,	kVerbMove,		-1,		 19 },
	{ 2,	kVerbOpen,		-1,		  9 },
	{ 2,	kVerbClose,		-1,		  9 },
	{ 2,	kVerbTalk,		-1,		 16 },
	// -------------------------------
	{ 3,	kVerbLook,		-1,		316 },
	{ 3,	kVerbMove,		-1,		317 },
	{ 3,	kVerbPick,		-1,		318 },
	{ 3,	kVerbOpen,		-1,		319 },
	{ 3,	kVerbClose,		-1,		319 },
	{ 3,	kVerbTalk,		-1,		320 },
	{ 3,	kVerbDefault,	-1,		318 },
	// -------------------------------
	{ 4,	kVerbMove,		-1,		 19 },
	{ 4,	kVerbOpen,		-1,		  9 },
	{ 4,	kVerbClose,		-1,		  9 },
	{ 4,	kVerbTalk,		-1,		 16 },
	// -------------------------------
	{ 5,	kVerbOpen,		-1,		  9 },
	{ 5,	kVerbClose,		-1,		  9 },
	{ 5,	kVerbTalk,		-1,		 16 },
	// -------------------------------
	{ 6,	kVerbMove,		-1,		 19 },
	{ 6,	kVerbOpen,		-1,		  9 },
	{ 6,	kVerbClose,		-1,		  9 },
	{ 6,	kVerbTalk,		-1,		 16 }
};

RoomTalkAction room1Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbPick,		118,	  5 },
	{ -1,	kVerbOpen,		118,	  3 },
	{ -1,	kVerbClose,		118,	  4 },
	{ -1,	kVerbTalk,		118,	  6 },
	// -------------------------------
	{ -1,	kVerbLook,		119,	  8 },
	{ -1,	kVerbMove,		119,	 13 },
	{ -1,	kVerbClose,		119,	 10 },
	{ -1,	kVerbTalk,		119,	 12 },
	// -------------------------------
	{ -1,	kVerbMove,		120,	 13 },
	{ -1,	kVerbOpen,		120,	 18 },
	{ -1,	kVerbTalk,		120,	 15 }
};

RoomTalkAction room3Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbLook,		129,	 21 },
	{ -1,	kVerbPick,		129,	  5 },
	{ -1,	kVerbMove,		129,	 24 },
	{ -1,	kVerbOpen,		129,	 22 },
	{ -1,	kVerbClose,		129,	 10 },
	// -------------------------------
	{ -1,	kVerbLook,		131,	 27 },
	{ -1,	kVerbPick,		131,	  5 },
	{ -1,	kVerbMove,		131,	 24 },
	{ -1,	kVerbOpen,		131,	 22 },
	{ -1,	kVerbClose,		131,	 10 },
	{ -1,	kVerbTalk,		131,	 23 },
	// -------------------------------
	{ -1,	kVerbLook,		132,	 28 },
	{ -1,	kVerbPick,		132,	  5 },
	{ -1,	kVerbMove,		132,	 24 },
	{ -1,	kVerbOpen,		132,	 22 },
	{ -1,	kVerbClose,		132,	 10 },
	{ -1,	kVerbTalk,		132,	 23 },
	// -------------------------------
	{ -1,	kVerbLook,		133,	321 },
	{ -1,	kVerbPick,		133,	 31 },
	{ -1,	kVerbMove,		133,	 34 },
	{ -1,	kVerbOpen,		133,	 30 },
	{ -1,	kVerbClose,		133,	 10 },
	// -------------------------------
	{ -1,	kVerbLook,		166,	 55 },
	{ -1,	kVerbPick,		166,	  7 },
	// -------------------------------
	{ -1,	kVerbLook,		211,	184 }
};

RoomTalkAction room4Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbLook,		189,	182 },
	// -------------------------------
	{ -1,	kVerbLook,		207,	175 },
	{ -1,	kVerbTalk,		207,	176 },
	// -------------------------------
	{ -1,	kVerbLook,		208,	177 },
	// -------------------------------
	{ -1,	kVerbLook,		209,	179 },
	// -------------------------------
	{ -1,	kVerbLook,		210,	180 },
	{ -1,	kVerbOpen,		210,	181 }
};

RoomTalkAction room5Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbMove,		136,	 13 },
	{ -1,	kVerbOpen,		136,	 18 },
	{ -1,	kVerbTalk,		136,	 15 },
	// -------------------------------
	{ -1,	kVerbLook,		212,	187 },
	{ -1,	kVerbTalk,		212,	188 },
	// -------------------------------
	{ -1,	kVerbLook,		213,	189 },
	{ -1,	kVerbOpen,		213,	190 }
};

RoomTalkAction room6Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbPick,		144,	 43 },
	// -------------------------------
	{ -1,	kVerbLook,		138,	 35 },
	{ -1,	kVerbTalk,		138,	  6 },
	// -------------------------------
	{ -1,	kVerbLook,		143,	 37 },
	{ -1,	kVerbPick,		143,	  7 },
	{ -1,	kVerbMove,		143,	  7 },
	{ -1,	kVerbTalk,		143,	 38 },
	// -------------------------------
	{ -1,	kVerbLook,		139,	 36 },
	// -------------------------------
	{ -1,	kVerbLook,		140,	147 }
};

RoomTalkAction room12Actions[] = {
	// num	action		object	speech
	{ -1,	kVerbLook,		154,	329 },
	{ -1,	kVerbTalk,		154,	330 },
	// -------------------------------
	{ -1,	kVerbMove,		155,	 48 },
	{ -1,	kVerbTalk,		155,	331 },
	// -------------------------------
	{ -1,	kVerbLook,		156,	 35 },
	{ -1,	kVerbMove,		156,	 48 },
	{ -1,	kVerbTalk,		156,	 50 },
};

bool DrasculaEngine::roomParse(RoomTalkAction* roomActions, int fl) {
	bool didAction = false;

	for (int i = 0; i < ARRAYSIZE(roomActions); i++) {
		if (roomActions[i].num == num_ejec || 
			roomActions[i].num == -1) {
			if (roomActions[i].action == pickedObject ||
				roomActions[i].action == kVerbDefault) {
				if (roomActions[i].objectID == fl ||
					roomActions[i].objectID == -1) {
					talk(roomActions[i].speechID);
					didAction = true;
					break;
				}
			}
		}
	}

	return didAction;
}

void DrasculaEngine::room_0() {
	if (roomParse(room0Actions, -1))
		return;

	// non-default actions
	if (num_ejec == 2) {
		if (pickedObject == kVerbLook) {
			talk(_text[_lang][mirar_t[c_mirar]], mirar_v[c_mirar]);
			c_mirar++;
			if (c_mirar == 3)
				c_mirar = 0;
		} else if (pickedObject == kVerbPick) {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		} else {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		}
	} else if (num_ejec == 4) {
		if (pickedObject == kVerbLook) {
			talk(_text[_lang][mirar_t[c_mirar]], mirar_v[c_mirar]);
			c_mirar++;
			if (c_mirar == 3)
				c_mirar = 0;
		} else if (pickedObject == kVerbPick) {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		} else {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		}
	} else if (num_ejec == 5) {
		if (pickedObject == kVerbLook) {
			talk(_text[_lang][mirar_t[c_mirar]], mirar_v[c_mirar]);
			c_mirar++;
			if (c_mirar == 3)
				c_mirar = 0;
		} else if (pickedObject == kVerbPick) {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		} else {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		}
	} else if (num_ejec == 6) {
		if (pickedObject == kVerbLook) {
			talk(_text[_lang][mirar_t[c_mirar]], mirar_v[c_mirar]);
			c_mirar++;
			if (c_mirar == 3)
				c_mirar = 0;
		} else if (pickedObject == kVerbPick) {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		} else {
			talk(_text[_lang][poder_t[c_poder]], poder_v[c_poder]);
			c_poder++;
			if (c_poder == 6)
				c_poder = 0;
		}
	}
}

void DrasculaEngine::room_1(int fl) {
	if (roomParse(room1Actions, fl))
		return;

	if (pickedObject == kVerbLook && fl == 118) {
		talk(1);
		pause(10);
		talk(2);
	} else if (pickedObject == kVerbLook && fl == 120 && flags[8] == 0)
		talk(14);
	else
		hay_answer = 0;
}

void DrasculaEngine::room_3(int fl) {
	if (roomParse(room3Actions, fl))
		return;

	if (pickedObject == kVerbTalk && fl == 129) {
		talk(23);
		pause(6);
		talk_sinc(_text[_lang][50], "50.als", "11111111111144432554433");
	} else if (pickedObject == kVerbTalk && fl == 133) {
		talk_sinc(_text[_lang][322], "322.als", "13333334125433333333");
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(25);
		talk(33);
	} else if (pickedObject == kVerbLook && fl == 165) {
		talk(149);
		talk(150);
	} else if (pickedObject == kVerbPick && fl == 165) {
		copyBackground(0, 0, 0,0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(44, 1, hare_x, hare_y, 41, 70, dir_dibujo2, dir_zona_pantalla);
		updateRefresh();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(4);
		pickObject(10);
		flags[3] = 1;
		visible[8] = 0;
	} else if (pickedObject == 14 && fl == 166 && flags[37] == 0) {
		animation_7_2();
		pickObject(8);
	} else if (pickedObject == 14 && fl == 166 && flags[37] == 1)
		talk(323);
	else if (pickedObject == kVerbTalk && fl == 211) {
		talk(185);
		talk(186);
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_4(int fl) {
	if (roomParse(room4Actions, fl))
		return;

	if (pickedObject == kVerbMove && fl == 189 && flags[34] == 0) {
		talk(327);
		pickObject(13);
		flags[34] = 1;
		if (flags[7] == 1 && flags[26] == 1 && flags[34] == 1 && flags[35] == 1 && flags[37] == 1)
			flags[38] = 1;
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_5(int fl) {
	if (roomParse(room5Actions, fl))
		return;

	if (pickedObject == kVerbLook && fl == 136 && flags[8] == 0) 
		talk(14);
	else if (pickedObject == 10 && fl == 136) {
		animation_5_2();
		resta_objeto(10);
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_6(int fl){
	if (roomParse(room6Actions, fl))
		return;

	if (pickedObject == kVerbLook && fl==144) {
		talk(41);
		talk(42);
	} else if (pickedObject == kVerbOpen && fl == 138)
		openDoor(0, 1);
	else if (pickedObject == kVerbClose && fl == 138)
		closeDoor(0, 1);
	else if (pickedObject == kVerbOpen && fl == 143 && flags[2] == 0) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(228, 102, hare_x + 5, hare_y - 1, 47, 73, dir_dibujo3, dir_zona_pantalla);
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(10);
		playSound("s3.als");
		flags[2] = 1;
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		stopSound();
	} else if (pickedObject == kVerbClose && fl == 143 && flags[2] == 1) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		flags[2] = 0;
		updateRefresh_pre();
		copyRect(228, 102, hare_x + 5, hare_y - 1, 47, 73, dir_dibujo3, dir_zona_pantalla);
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(5);
		playSound("s4.als");
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		stopSound();
	} else if (pickedObject == kVerbOpen && fl == 139 && flags[1] == 0) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(267, 1, hare_x - 14, hare_y - 2, 52, 73, dir_dibujo3, dir_zona_pantalla);
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(19);
		playSound("s3.als");
		flags[1] = 1;
		visible[4] = 1;
		visible[2] = 0;
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		stopSound();
	} else if (pickedObject == kVerbPick && fl == 140) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(267, 1, hare_x - 14, hare_y - 2, 52, 73, dir_dibujo3, dir_zona_pantalla);
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(19);
		pickObject(9);
		visible[4] = 0;
		flags[10] = 1;
	} else if (pickedObject == kVerbOpen && fl == 140)
		hay_answer = 1;
	else
		hay_answer = 0;
}

void DrasculaEngine::room_7(int fl){
	if (pickedObject == kVerbLook && fl == 169)
		talk(44);
	else if (pickedObject == kVerbLook && fl == 164)
		talk(35);
	else if (pickedObject == kVerbPick && fl == 190) {
		pickObject(17);
		flags[35] = 1;
		visible[3] = 0;
		if (flags[7] == 1 && flags[26] == 1 && flags[34] == 1 && flags[35] == 1 && flags[37] == 1)
			flags[38] = 1;
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_8(int fl) {
	if (pickedObject == kVerbLook && fl == 147 && flags[7] == 0) {
		talk(58);
		pickObject(15);
		flags[7] = 1;
		if (flags[7] == 1 && flags[26] == 1 && flags[34] == 1 && flags[35] == 1 && flags[37] == 1)
			flags[38] = 1;
	} else if (pickedObject == kVerbLook && fl == 147)
		talk(59);
	else
		hay_answer = 0;
}

void DrasculaEngine::room_9(int fl){
	if (pickedObject == kVerbLook && fl == 150)
		talk(35);
	else if (pickedObject == kVerbTalk && fl == 150)
		talk(6);
	else if (pickedObject == kVerbLook && fl == 51)
		talk(60);
	else if (pickedObject == kVerbTalk && fl == 51 && flags[4] == 0)
		animation_4_2();
	else if (pickedObject == kVerbTalk && fl == 51 && flags[4] == 1)
		animation_33_2();
	else if (pickedObject == 7 && fl == 51) {
		animation_6_2();
		resta_objeto(7);
		pickObject(14);}
	else
		hay_answer = 0;
}

void DrasculaEngine::room_12(int fl){
	if (roomParse(room12Actions, fl))
		return;

	if (pickedObject == kVerbOpen && fl == 156)
		openDoor(16, 4);
	else if (pickedObject == kVerbClose && fl == 156)
		closeDoor(16, 4);
	else
		hay_answer = 0;
}

bool DrasculaEngine::room_13(int fl) {
	if (pickedObject == kVerbLook && fl == 51) {
		talk(411);
		sentido_hare = 3;
		talk(412);
		strcpy(objName[1], "yoda");
	} else if (pickedObject == kVerbTalk && fl == 51)
		conversa("op_7.cal");
	else if (pickedObject == 19 && fl == 51)
		animation_1_3();
	else if (pickedObject == 9 && fl == 51) {
		animation_2_3();
		return true;
	} else
		hay_answer = 0;
	return false;
}

void DrasculaEngine::room_14(int fl) {
	if (pickedObject == kVerbTalk && fl == 54 && flags[39] == 0)
		animation_12_2();
	else if (pickedObject == kVerbTalk && fl == 54 && flags[39] == 1)
		talk(109);
	else if (pickedObject == 12 && fl == 54)
		animation_26_2();
	else if (pickedObject == kVerbTalk && fl == 52 && flags[5] == 0)
		animation_11_2();
	else if (pickedObject == kVerbTalk && fl == 52 && flags[5] == 1)
		animation_36_2();
	else if (pickedObject == kVerbTalk && fl == 53)
		animation_13_2();
	else if (pickedObject == kVerbLook && fl == 200)
		talk(165);
	else if (pickedObject == kVerbLook && fl == 201)
		talk(166);
	else if (pickedObject == kVerbLook && fl == 202)
		talk(167);
	else if (pickedObject == kVerbLook && fl == 203)
		talk(168);
	else if (pickedObject == kVerbPick && fl == 203)
		talk(170);
	else if (pickedObject == kVerbMove && fl == 203)
		talk(170);
	else if (pickedObject == kVerbTalk && fl == 203)
		talk(169);
	else if (pickedObject == kVerbLook && fl == 204)
		talk(171);
	else
		hay_answer = 0;
}

void DrasculaEngine::room_15(int fl) {
	if (pickedObject == kVerbTalk && fl == 188)
		talk(333);
	else if (pickedObject == kVerbLook && fl == 188)
		talk(334);
	else if (pickedObject == 19 && fl == 188 && flags[27] == 0)
		talk(335);
	else if (pickedObject == 19 && fl == 188 && flags[27] == 1) {
		talk(336);
		sentido_hare = 3;
		talk(337);
		talk_sinc(_text[_lang][46], "46.als", "4442444244244");
		sentido_hare = 1;
	} else if (pickedObject == 18 && fl == 188 && flags[26] == 0) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		copyRect(133, 135, hare_x + 6, hare_y, 39, 63, dir_dibujo3, dir_zona_pantalla);
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		playSound("s8.als");
		stopSound();
		talk(_text[_lang][338], "338.als");
		flags[27] = 0;
		pickObject(19);
		resta_objeto(18);
	} else if (pickedObject == kVerbMove && fl == 188 && flags[27] == 0) {
		animation_34_2();
		talk(339);
		pickObject(16);
		flags[26] = 1;
		flags[27] = 1;
		if (flags[7] == 1 && flags[26] == 1 && flags[34] == 1 && flags[35] == 1 && flags[37] == 1)
			flags[38] = 1;
	} else if (pickedObject == kVerbLook && fl == 205)
		talk(172);
	else if (pickedObject == kVerbLook && fl == 206)
		talk(173);
	else if (pickedObject == kVerbMove && fl == 206)
		talk(174);
	else if (pickedObject == kVerbOpen && fl == 206)
		talk(174);
	else
		hay_answer = 0;
}

void DrasculaEngine::room_16(int fl) {
	if (pickedObject == kVerbTalk && fl == 163)
		talk(_text[_lang][6], "6.als");
	else if (pickedObject == kVerbOpen && fl == 163)
		openDoor(17, 0);
	else if (pickedObject == kVerbClose && fl == 163)
		closeDoor(17, 0);
	else if (pickedObject == kVerbLook && fl == 183)
		talk(_text[_lang][340], "340.als");
	else if (pickedObject == kVerbTalk && fl == 183) {
		talk(_text[_lang][341], "341.als");
		pause(10);
		talk_sinc(_text[_lang][50], "50.als", "11111111111144432554433");
		pause(3);
		talk_baul(_text[_lang][83], "d83.als");
	} else if (pickedObject == kVerbOpen && fl == 183) {
		openDoor(19, NO_DOOR);
		if (flags[20] == 0) {
			flags[20] = 1;
			sentido_hare = 3;
			updateRoom();
			updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
			talk(_text[_lang][342], "342.als");
			pickObject(22);
		}
	} else if (pickedObject == kVerbClose && fl == 183)
		closeDoor(19, NO_DOOR);
	else if (pickedObject == kVerbLook && fl == 185)
		talk(_text[_lang][37], "37.als");
	else if (pickedObject == kVerbPick && fl == 185)
		talk(_text[_lang][7], "7.als");
	else if (pickedObject == kVerbMove && fl == 185)
		talk(_text[_lang][7], "7.als");
	else if (pickedObject == kVerbTalk && fl == 185)
		talk(_text[_lang][38], "38.als");
	else if (pickedObject == kVerbLook && fl == 187) {
		talk(_text[_lang][343], "343.als");
		sentido_hare = 3;
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		talk(_text[_lang][344], "344.als");
	} else if (pickedObject == kVerbTalk && fl == 187)
		talk(_text[_lang][345], "345.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_17(int fl) {
	if (pickedObject == kVerbLook && fl == 177)
		talk(_text[_lang][35], "35.als");
	else if (pickedObject == kVerbTalk && fl == 177 && flags[18] == 0)
		talk(_text[_lang][6], "6.als");
	else if (pickedObject == kVerbTalk && fl == 177 && flags[18] == 1)
		animation_18_2();
	else if (pickedObject == kVerbOpen && fl == 177 && flags[18] == 1)
		talk(_text[_lang][346], "346.als");
	else if (pickedObject == kVerbOpen && fl == 177 && flags[14] == 0 && flags[18] == 0)
		animation_22_2();
	else if (pickedObject == kVerbOpen && fl == 177 && flags[14] == 1)
		openDoor(15, 1);
	else if (pickedObject == kVerbClose && fl == 177 && flags[14] == 1)
		closeDoor(15, 1);
	else if (pickedObject == 11 && fl == 50 && flags[22] == 0) {
		talk(_text[_lang][347], "347.als");
		flags[29] = 1;
		pickObject(23);
		resta_objeto(11);
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_18(int fl) {
	if (pickedObject == kVerbTalk && fl == 55 && flags[36] == 0)
		animation_24_2();
	else if (pickedObject == kVerbTalk && fl == 55 && flags[36] == 1)
		talk(_text[_lang][109], "109.als");
	else if (pickedObject == kVerbLook && fl == 181)
		talk(_text[_lang][348], "348.als");
	else if (pickedObject == kVerbPick && fl == 182) {
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(44, 1, hare_x, hare_y, 41, 70, dir_dibujo2, dir_zona_pantalla);
		updateRefresh();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(4);
		pickObject(12);
		visible[2] = 0;
		flags[28] = 1;
	} else if (pickedObject == kVerbLook && fl == 182)
		talk(_text[_lang][154], "154.als");
	else if (pickedObject == 8 && fl == 55 && flags[38] == 0 && flags[33] == 1)
		talk(_text[_lang][349], "349.als");
	else if (pickedObject == 13 && fl == 55 && flags[38] == 0 && flags[33] == 1)
		talk(_text[_lang][349], "349.als");
	else if (pickedObject == 15 && fl == 55 && flags[38] == 0 && flags[33] == 1)
		talk(_text[_lang][349], "349.als");
	else if (pickedObject == 16 && fl == 55 && flags[38] == 0 && flags[33] == 1)
		talk(_text[_lang][349], "349.als");
	else if (pickedObject == 17 && fl == 55 && flags[38] == 0 && flags[33] == 1)
		talk(_text[_lang][349], "349.als");
	else if (pickedObject == 8 && fl == 55 && flags[38] == 1 && flags[33] == 1)
		animation_24_2();
	else if (pickedObject == 13 && fl == 55 && flags[38] == 1 && flags[33] == 1)
		animation_24_2();
	else if (pickedObject == 15 && fl == 55 && flags[38] == 1 && flags[33] == 1)
		animation_24_2();
	else if (pickedObject == 16 && fl == 55 && flags[38] == 1 && flags[33] == 1)
		animation_24_2();
	else if (pickedObject == 17 && fl == 55 && flags[38] == 1 && flags[33] == 1)
		animation_24_2();
	else if (pickedObject == 11 && fl == 50 && flags[22] == 0) {
		sentido_hare = 3;
		updateRoom();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		copyBackground(0, 0, 0, 0, 320, 200, dir_dibujo1, dir_zona_pantalla);
		updateRefresh_pre();
		copyRect(1, 1, hare_x - 1, hare_y + 3, 42, 67, dir_dibujo2, dir_zona_pantalla);
		updateRefresh();
		updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
		pause(6);
		talk(_text[_lang][347], "347.als");
		flags[29] = 1;
		pickObject(23);
		resta_objeto(11);
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_19(int fl) {
	if (pickedObject == kVerbLook && fl == 214)
		talk(_text[_lang][191], "191.als");
	else
		hay_answer = 0;
}

bool DrasculaEngine::room_21(int fl) {
	if (pickedObject == kVerbOpen && fl == 101 && flags[28] == 0)
		talk(_text[_lang][419], "419.als");
	else if (pickedObject == kVerbOpen && fl == 101 && flags[28] == 1)
		openDoor(0, 1);
	else if (pickedObject == kVerbClose && fl == 101)
		closeDoor(0, 1);
	else if(pickedObject == kVerbPick && fl == 141) {
		pickObject(19);
		visible[2] = 0;
		flags[10] = 1;
	} else if(pickedObject == 7 && fl == 101) {
		flags[28] = 1;
		openDoor(0, 1);
		withoutVerb();
	} else if (pickedObject == 21 && fl == 179) {
		animation_9_4();
		return true;
	} else
		hay_answer = 0;

	return false;
}

void DrasculaEngine::room_22(int fl) {
	if (pickedObject == kVerbPick && fl == 140)
		talk(_text[_lang][7], "7.als");
	else if (pickedObject == 11 && fl == 140) {
		pickObject(18);
		visible[1] = 0;
		flags[24] = 1;
	} else if (pickedObject == 22 && fl == 52) {
		anima("up.bin",14);
		flags[26]=1;
		playSound("s1.als");
		hipo(14);
		stopSound();
		withoutVerb();
		resta_objeto(22);
		updateData();
		sentido_hare = 3;
		talk(_text[_lang][499], "499.als");
		talk(_text[_lang][500], "500.als");
	} else if (pickedObject == kVerbLook && fl == 52)
		talk(_text[_lang][497], "497.als");
	else if (pickedObject == kVerbTalk && fl == 52)
		talk(_text[_lang][498], "498.als");
	else if (pickedObject == kVerbPick && fl == 180 && flags[26] == 0)
		talk(_text[_lang][420], "420.als");
	else if (pickedObject == kVerbPick && fl == 180 && flags[26] == 1) {
		pickObject(7);
		visible[3] = 0;
		flags[27] = 1;
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_23(int fl) {
	if (pickedObject == kVerbOpen && fl == 103) {
		openDoor(0, 0);
		updateData();
	} else if(pickedObject == kVerbClose && fl == 103) {
		closeDoor(0, 0);
		updateData();
	} else if(pickedObject == kVerbOpen && fl == 104)
		openDoor(1, 1);
	else if(pickedObject == kVerbClose && fl == 104)
		closeDoor(1, 1);
	else if(pickedObject == kVerbPick && fl == 142) {
		pickObject(8);
		visible[2] = 0;
		flags[11] = 1;
		if (flags[22] == 1 && flags[14] == 1)
			flags[18] = 1;
		if (flags[18] == 1)
			animation_6_4();
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_24(int fl) {
	if (pickedObject == kVerbOpen && fl == 105)
		openDoor(1, 0);
	else if (pickedObject == kVerbClose && fl == 105)
		closeDoor(1, 0);
	else if (pickedObject == kVerbOpen && fl == 106)
		openDoor(2, 1);
	else if (pickedObject == kVerbClose && fl == 106)
		closeDoor(2, 1);
	else if (pickedObject == kVerbLook && fl == 151)
		talk(_text[_lang][461], "461.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_26(int fl) {
	if (pickedObject == kVerbOpen && fl == 107 && flags[30] == 0)
		openDoor(2, 0);
	else if (pickedObject == kVerbOpen && fl == 107 && flags[30] == 1)
		talk(_text[_lang][421], "421.als");
	else if (pickedObject == kVerbClose && fl == 107)
		closeDoor(2, 0);
	else if (pickedObject == 10 && fl == 50 && flags[18] == 1 && flags[12] == 1)
		animation_5_4();
	else if (pickedObject == 8 && fl == 50 && flags[18] == 1 && flags[12] == 1)
		animation_5_4();
	else if (pickedObject == 12 && fl == 50 && flags[18] == 1 && flags[12] == 1)
		animation_5_4();
	else if (pickedObject == 16 && fl == 50 && flags[18] == 1 && flags[12] == 1)
		animation_5_4();
	else if (pickedObject == kVerbPick && fl == 143 && flags[18] == 1) {
		lleva_al_hare(260, 180);
		pickObject(10);
		visible[1] = 0;
		flags[12] = 1;
		closeDoor(2, 0);
		sentido_hare = 2;
		talk_igorpuerta(_texti[_lang][27], "I27.als");
		flags[30] = 1;
		talk_igorpuerta(_texti[_lang][28], "I28.als");
		lleva_al_hare(153, 180);
	} else if (pickedObject == kVerbPick && fl == 143 && flags[18] == 0) {
		lleva_al_hare(260, 180);
		copyBackground(80, 78, 199, 94, 38, 27, dir_dibujo3, dir_zona_pantalla);
		updateScreen(199, 94, 199, 94, 38, 27, dir_zona_pantalla);
		pause(3);
		talk_igor_peluca(_texti[_lang][25], "I25.als");
		lleva_al_hare(153, 180);
	} else if (pickedObject == kVerbTalk && fl == 51)
		animation_1_4();
	else if (pickedObject == kVerbOpen && fl == 167)
		talk(_text[_lang][467], "467.als");
	else if (pickedObject == kVerbLook && fl == 164)
		talk(_text[_lang][470], "470.als");
	else if (pickedObject == kVerbOpen && fl == 164)
		talk(_text[_lang][471], "471.als");
	else if (pickedObject == kVerbLook && fl == 163)
		talk(_text[_lang][472], "472.als");
	else if (pickedObject == kVerbPick && fl == 163)
		talk(_text[_lang][473], "473.als");
	else if (pickedObject == kVerbLook && fl == 165)
		talk(_text[_lang][474], "474.als");
	else if (pickedObject == kVerbLook && fl == 168)
		talk(_text[_lang][476], "476.als");
	else if (pickedObject == kVerbPick && fl == 168)
		talk(_text[_lang][477], "477.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_27(int fl) {
	if (pickedObject == kVerbOpen && fl == 110)
		openDoor(6, 1);
	else if (pickedObject == kVerbClose && fl == 110)
		closeDoor(6, 1);
	else if (pickedObject == kVerbOpen && fl == 116 && flags[23] == 0)
		talk(_text[_lang][419], "419.als");
	else if (pickedObject == kVerbOpen && fl == 116 && flags[23] == 1)
		openDoor(5, 3);
	else if (pickedObject == 17 && fl == 116) {
		flags[23] = 1;
		openDoor(5,3);
		withoutVerb();
	} else if (pickedObject == kVerbLook && fl == 175)
		talk(_text[_lang][429], "429.als");
	else if (fl == 150)
		talk(_text[_lang][460], "460.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_29(int fl) {
	if (pickedObject == kVerbOpen && fl == 114)
		openDoor(4, 1);
	else if (pickedObject == kVerbClose && fl == 114)
		closeDoor(4, 1);
	else if (pickedObject == kVerbLook && fl == 152)
		talk(_text[_lang][463], "463.als");
	else if (pickedObject == kVerbOpen && fl == 152)
		talk(_text[_lang][464], "464.als");
	else if (pickedObject == kVerbLook && fl == 153)
		talk(_text[_lang][465], "465.als");
	else if (pickedObject == kVerbPick && fl == 154)
		talk(_text[_lang][466], "466.als");
	else if (pickedObject == kVerbOpen && fl == 156)
		talk(_text[_lang][467], "467.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_30(int fl) {
	if (pickedObject == kVerbOpen && fl == 115)
		openDoor(4, 0);
	else if (pickedObject == kVerbClose && fl == 115)
		closeDoor(4, 0);
	else if (pickedObject == kVerbOpen && fl == 144 && flags[19] == 0)
		talk(_text[_lang][422], "422.als");
	else if (pickedObject == kVerbOpen && fl == 144 && flags[19] == 1 && flags[22] == 1)
		openDoor(16, 1);
	else if (pickedObject == kVerbOpen && fl == 144 && flags[19] == 1 && flags[22] == 0) {
		openDoor(16, 1);
		talk(_text[_lang][423], "423.als");
		flags[22] = 1;
		pickObject(12);
		if (flags[11] == 1 && flags[14] == 1)
			flags[18] = 1;
		if (flags[18] == 1)
			animation_6_4();
	} else if (pickedObject == kVerbClose && fl == 144)
		closeDoor(16, 1);
	else if (pickedObject == 13 && fl == 144) {
		talk(_text[_lang][424], "424.als");
		flags[19] = 1;
	} else if (pickedObject == kVerbOpen && fl == 157)
		talk(_text[_lang][468], "468.als");
	else if (pickedObject == kVerbLook && fl == 158)
		talk(_text[_lang][469], "469.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_31(int fl) {
	if (pickedObject == kVerbPick && fl == 145) {
		pickObject(11);
		visible[1] = 0;
		flags[13] = 1;
	} else if (pickedObject == kVerbOpen && fl == 117)
		openDoor(5, 0);
	else if (pickedObject == kVerbClose && fl == 117)
		closeDoor(5, 0);
	else if (pickedObject == kVerbLook && fl == 161)
		talk(_text[_lang][470], "470.als");
	else if (pickedObject == kVerbOpen && fl == 161)
		talk(_text[_lang][471], "471.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_34(int fl) {
	if (pickedObject == kVerbMove && fl == 146)
		animation_8_4();
	else if (pickedObject == kVerbLook && fl == 146)
		talk(_text[_lang][458], "458.als");
	else if (pickedObject == kVerbPick && fl == 146)
		talk(_text[_lang][459], "459.als");
	else if (pickedObject == kVerbOpen && fl == 120 && flags[25] == 1)
		openDoor(8, 2);
	else if (pickedObject == kVerbOpen && fl == 120 && flags[25] == 0) {
		openDoor(8, 2);
		sentido_hare = 3;
		talk(_text[_lang][425], "425.als");
		pickObject(14);
		flags[25] = 1;
	} else if (pickedObject == kVerbClose && fl == 120)
		closeDoor(8, 2);
	else
		hay_answer=0;
}

void DrasculaEngine::room_35(int fl) {
	if (pickedObject == kVerbPick && fl == 148) {
		pickObject(16);
		visible[2] = 0;
		flags[14] = 1;
	if (flags[11] == 1 && flags[22] == 1)
		flags[18] = 1;
	if (flags[18] == 1)
		animation_6_4();
	} else if (pickedObject == kVerbPick && fl == 147) {
		talk(_text[_lang][426], "426.als");
		pickObject(15);
		visible[1] = 0;
		flags[15] = 1;
		flags[17] = 1;
		updateData();
	} else if (pickedObject == kVerbPick && fl == 149) {
		pickObject(13);
		visible[3] = 0;
		flags[17] = 0;
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_44(int fl) {
	if (pickedObject == kVerbLook && fl == 172)
		talk(_text[_lang][428], "428.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_49(int fl){
	if (pickedObject == kVerbTalk && fl ==51)
		conversa("op_9.cal");
	else if (pickedObject == kVerbLook && fl == 51)
		talk(_text[_lang][132], "132.als");
	else if ((pickedObject == 8 && fl == 51) || (pickedObject == 8 && fl == 203))
		animation_5_5();
	else if (pickedObject == kVerbLook && fl == 200)
		talk(_text[_lang][133], "133.als");
	else if (pickedObject == kVerbTalk && fl == 200)
		talk(_text[_lang][134], "134.als");
	else if (pickedObject == kVerbLook && fl == 201)
		talk(_text[_lang][135], "135.als");
	else if (pickedObject == kVerbLook && fl == 203)
		talk(_text[_lang][137], "137.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_53(int fl) {
	if (pickedObject == kVerbPick && fl == 120) {
		pickObject(16);
		visible[3] = 0;
	} else if (pickedObject == kVerbLook && fl == 121)
		talk(_text[_lang][128], "128.als");
	else if (pickedObject == kVerbLook && fl == 209)
		talk(_text[_lang][129], "129.als");
	else if (pickedObject == kVerbMove && fl == 123)
		animation_11_5();
	else if (pickedObject == kVerbLook && fl == 52)
		talk(_text[_lang][447], "447.als");
	else if (pickedObject == kVerbTalk && fl == 52)
		talk(_text[_lang][131], "131.als");
	else if (pickedObject == 12 && fl == 52)
		animation_10_5();
	else if (pickedObject == 15 && fl == 52)
		animation_9_5();
	else if (pickedObject == 16 && fl == 121) {
		flags[2] = 1;
		withoutVerb();
		updateData();
	} else if (pickedObject == 16) {
		talk(_text[_lang][439], "439.als");
		withoutVerb();
		visible[3] = 1;
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_54(int fl) {
	if ((pickedObject == kVerbTalk && fl == 118) || (pickedObject == kVerbLook && fl == 118 && flags[0] == 0))
		animation_1_5();
	else if (pickedObject == kVerbLook && fl == 118 && flags[0]==1)
		talk(_text[_lang][124], "124.als");
	else if (pickedObject == kVerbLook && fl == 53)
		talk(_text[_lang][127], "127.als");
	else if (pickedObject == kVerbTalk && fl == 53 && flags[14] == 0) {
		talk(_text[_lang][288], "288.als");
		flags[12] = 1;
		pause(10);
		talk_mus(_texte[_lang][1], "E1.als");
		talk(_text[_lang][289], "289.als");
		talk_mus(_texte[_lang][2], "E2.als");
		talk_mus(_texte[_lang][3], "E3.als");
		conversa("op_10.cal");
		flags[12] = 0;
		flags[14] = 1;
	} else if (pickedObject == kVerbTalk && fl == 53 && flags[14] == 1)
		talk(_text[_lang][109], "109.als");
	else if (pickedObject == kVerbPick && fl == 9999 && flags[13] == 0) {
		pickObject(8);
		flags[13] = 1;
		talk_mus(_texte[_lang][10], "e10.als");
		updateData();
	} else if (pickedObject == kVerbOpen && fl == 119)
		talk(_text[_lang][125], "125.als");
	else if (pickedObject == kVerbLook && fl == 119)
		talk(_text[_lang][126], "126.als");
	else if (pickedObject == 10 && fl == 119) {
		pause(4);
		talk(_text[_lang][436], "436.als");
		withoutVerb();
		resta_objeto(10);
	} else
		hay_answer = 0;
}

void DrasculaEngine::room_55(int fl) {
	if (pickedObject == kVerbPick && fl == 122) {
		pickObject(12);
		flags[8] = 1;
		updateData();
	} else if (pickedObject == kVerbLook && fl == 122)
		talk(_text[_lang][138], "138.als");
	else if (pickedObject == kVerbLook && fl == 204)
		talk(_text[_lang][139], "139.als");
	else if (pickedObject == kVerbLook && fl == 205)
		talk(_text[_lang][140], "140.als");
	else if (fl == 206) {
		playSound("s11.als");
		anima("det.bin", 17);
		stopSound();
		lleva_al_hare(hare_x - 3, hare_y + alto_hare + 6);
	} else
		hay_answer = 0;
}

bool DrasculaEngine::room_56(int fl) {
	if (pickedObject == kVerbOpen && fl == 124) {
		animation_14_5();
		return true;
	} else if (pickedObject == kVerbLook && fl == 124)
		talk(_text[_lang][450], "450.als");
	else if (pickedObject == kVerbOpen && fl == 207)
		talk(_text[_lang][141], "141.als");
	else if (pickedObject == kVerbLook && fl == 208)
		talk(_text[_lang][142], "142.als");
	else
		hay_answer = 0;

	return false;
}

void DrasculaEngine::room_58(int fl) {
	if (pickedObject == kVerbMove && fl == 103)
		animation_7_6();
	else if (pickedObject == kVerbLook && fl == 104)
		talk(_text[_lang][454], "454.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_59(int fl) {
	if ((pickedObject == kVerbTalk && fl == 51) || (pickedObject == kVerbLook && fl == 51)) {
		flags[9] = 1;
		talk(_text[_lang][259], "259.als");
		talk_bj_cama(_textbj[_lang][13], "bj13.als");
		talk(_text[_lang][263], "263.als");
		talk_bj_cama(_textbj[_lang][14], "bj14.als");
		pause(40);
		talk(_text[_lang][264], "264.als");
		talk_bj_cama(_textbj[_lang][15], "BJ15.als");
		talk(_text[_lang][265], "265.als");
		flags[9] = 0;
		if (flags[11] == 0) {
			playSound("s12.als");
			delay(40);
			stopSound();
			delay(10);
			lleva_al_hare(174, 168);
			sentido_hare = 2;
			updateRoom();
			updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
			pause(40);
			playSound("s12.als");
			pause(19);
			stopSound_corte();
			hare_se_ve = 0;
			updateRoom();
			copyRect(101, 34, hare_x - 4, hare_y - 1, 37, 70, dir_dibujo3, dir_zona_pantalla);
			copyBackground(0, 0, 0, 0, 320, 200, dir_zona_pantalla, dir_dibujo1);
			updateScreen(0, 0, 0, 0, 320, 200, dir_zona_pantalla);
			hare_se_ve = 1;
			clearRoom();
			loadPic("tlef0.alg");
			decompressPic(dir_dibujo1, COMPLETE_PAL);
			loadPic("tlef1.alg");
			decompressPic(dir_dibujo3, 1);
			loadPic("tlef2.alg");
			decompressPic(dir_hare_frente, 1);
			loadPic("tlef3.alg");
			decompressPic(dir_hare_fondo, 1);
			talk_htel(_text[_lang][240], "240.als");

			color_abc(VON_BRAUN);
			talk_solo(_textvb[_lang][58], "VB58.als");
			talk_htel(_text[_lang][241], "241.als");
			color_abc(VON_BRAUN);
			talk_solo(_textvb[_lang][59], "VB59.als");
			talk_htel(_text[_lang][242], "242.als");
			color_abc(VON_BRAUN);
			talk_solo(_textvb[_lang][60], "VB60.als");
			talk_htel(_text[_lang][196], "196.als");
			color_abc(VON_BRAUN);
			talk_solo(_textvb[_lang][61],"VB61.als");
			talk_htel(_text[_lang][244], "244.als");
			color_abc(VON_BRAUN);
			talk_solo(_textvb[_lang][62], "VB62.als");
			clearRoom();
			loadPic("aux59.alg");
			decompressPic(dir_dibujo3, 1);
			loadPic("96.alg");
			decompressPic(dir_hare_frente, COMPLETE_PAL);
			loadPic("99.alg");
			decompressPic(dir_hare_fondo, 1);
			loadPic("59.alg");
			decompressPic(dir_dibujo1, HALF_PAL);
			sentido_hare = 3;
			talk(_text[_lang][245], "245.als");
			withoutVerb();
			flags[11] = 1;
		}
	} else
		hay_answer = 0;
}

bool DrasculaEngine::room_60(int fl) {
	if (pickedObject == kVerbMove && fl == 112)
		animation_10_6();
	else if (pickedObject == kVerbLook && fl == 112)
		talk(_text[_lang][440], "440.als");
	else if (pickedObject == kVerbTalk && fl == 52) {
		talk(_text[_lang][266], "266.als");
		talk_taber2(_textt[_lang][1], "t1.als");
		conversa("op_12.cal");
		withoutVerb();
		pickedObject = 0;
	} else if (pickedObject == kVerbTalk && fl == 115)
		talk(_text[_lang][455], "455.als");
	else if (pickedObject == kVerbTalk && fl == 56)
		talk(_text[_lang][455], "455.als");
	else if (pickedObject == kVerbLook && fl == 114)
		talk(_text[_lang][167], "167.als");
	else if (pickedObject == kVerbLook && fl == 113)
		talk(_text[_lang][168], "168.als");
	else if (pickedObject == kVerbPick && fl == 113)
		talk(_text[_lang][170], "170.als");
	else if (pickedObject == kVerbMove && fl == 113)
		talk(_text[_lang][170], "170.als");
	else if (pickedObject == kVerbTalk && fl == 113)
		talk(_text[_lang][169], "169.als");
	else if (pickedObject == 21 && fl == 56)
		animation_18_6();
	else if (pickedObject == 9 && fl == 56 && flags[6] == 1) {
		animation_9_6();
		return true;
	} else if (pickedObject == 9 && fl == 56 && flags[6] == 0) {
		anima("cnf.bin", 14);
		talk(_text[_lang][455], "455.als");
	} else
		hay_answer = 0;

	return false;
}

void DrasculaEngine::room_61(int fl) {
	if (pickedObject == kVerbLook && fl == 116)
		talk(_text[_lang][172], "172.als");
	else if (pickedObject == kVerbLook && fl == 117)
		talk(_text[_lang][173], "173.als");
	else if (pickedObject == kVerbMove && fl == 117)
		talk(_text[_lang][174], "174.als");
	else if (pickedObject == kVerbOpen && fl == 117)
		talk(_text[_lang][174], "174.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_62(int fl) {
	if (pickedObject == kVerbTalk && fl == 53)
		conversa("op_13.cal");
	else if (pickedObject == kVerbTalk && fl == 52 && flags[0] == 0)
		animation_3_1();
	else if (pickedObject == kVerbTalk && fl == 52 && flags[0] == 1)
		talk(_text[_lang][109], "109.als");
	else if (pickedObject == kVerbTalk && fl == 54)
		animation_4_1();
	else if (pickedObject == kVerbLook && fl == 100)
		talk(_text[_lang][168], "168.als");
	else if (pickedObject == kVerbTalk && fl == 100)
		talk(_text[_lang][169], "169.als");
	else if (pickedObject == kVerbPick && fl == 100)
		talk(_text[_lang][170], "170.als");
	else if (pickedObject == kVerbLook && fl == 101)
		talk(_text[_lang][171], "171.als");
	else if (pickedObject == kVerbLook && fl == 102)
		talk(_text[_lang][167], "167.als");
	else if (pickedObject == kVerbLook && fl == 103)
		talk(_text[_lang][166], "166.als");
	else hay_answer = 0;
}

void DrasculaEngine::room_63(int fl) {
	if (pickedObject == kVerbLook && fl == 110)
		talk(_text[_lang][172], "172.als");
	else if (pickedObject == kVerbLook && fl == 109)
		talk(_text[_lang][173], "173.als");
	else if (pickedObject == kVerbMove && fl == 109)
		talk(_text[_lang][174], "174.als");
	else if (pickedObject == kVerbLook && fl == 108)
		talk(_text[_lang][334], "334.als");
	else if (pickedObject == kVerbTalk && fl == 108)
		talk(_text[_lang][333], "333.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::room_pendulo(int fl) {
	if (pickedObject == kVerbLook && fl == 100)
		talk(_text[_lang][452], "452.als");
	else if (pickedObject == kVerbLook && fl == 101)
		talk (_text[_lang][123], "123.als");
	else if (pickedObject == kVerbPick && fl == 101)
		pickObject(20);
	else if (pickedObject == 20 && fl == 100)
		animation_6_6();
	else if (pickedObject == kVerbPick || pickedObject == kVerbOpen)
		talk(_text[_lang][453], "453.als");
	else
		hay_answer = 0;
}

void DrasculaEngine::updateRefresh() {
	if (num_ejec == 1) {
		if (roomNumber == 63)
			update_63();
		else if (roomNumber == 62)
			update_62();
	} else if (num_ejec == 2) {
		if (roomNumber == 3)
			update_3();
		else if (roomNumber == 2)
			update_2();
		else if (roomNumber == 4)
			update_4();
		else if (roomNumber == 5)
			update_5();
		else if (roomNumber == 15)
			update_15();
		else if (roomNumber == 17)
			update_17();
		else if (roomNumber == 18)
			update_18();
		else if (roomNumber == 10)
			mapa();
	} else if (num_ejec == 3) {
		if (roomNumber == 20)
			update_20();
		else if (roomNumber == 13)
			update_13();
	} else if (num_ejec == 4) {
		if (roomNumber == 29)
			update_29();
		else if (roomNumber == 26)
			update_26();
		else if (roomNumber == 27)
			update_27();
		else if (roomNumber == 31)
			update_31();
		else if (roomNumber == 34)
			update_34();
		else if (roomNumber == 35)
			update_35();
	} else if (num_ejec == 5) {
		if (roomNumber == 45)
			mapa();
		else if (roomNumber == 50)
			update_50();
		else if (roomNumber == 57)
			update_57();
	} else if (num_ejec == 6) {
		if (roomNumber == 60)
			update_60();
		else if (roomNumber == 61)
			update_61();
		else if (roomNumber == 58)
			update_58();
	}
}

void DrasculaEngine::updateRefresh_pre() {
	if (num_ejec == 1) {
		if (roomNumber == 62)
			update_62_pre();
		else if (roomNumber == 16)
			pon_bj();
	} else if (num_ejec == 2) {
		if (roomNumber == 1)
			update_1_pre();
		else if (roomNumber == 3)
			update_3_pre();
		else if (roomNumber == 5)
			update_5_pre();
		else if (roomNumber == 6)
			update_6_pre();
		else if (roomNumber == 7)
			update_7_pre();
		else if (roomNumber == 9)
			update_9_pre();
		else if (roomNumber == 12)
			update_12_pre();
		else if (roomNumber == 14)
			update_14_pre();
		else if (roomNumber == 16)
			update_16_pre();
		else if (roomNumber == 17)
			update_17_pre();
		else if (roomNumber == 18)
			update_18_pre();
	} else if (num_ejec == 3) {
		// nothing
	} else if (num_ejec == 4) {
		if (roomNumber == 21)
			update_21_pre();
		else if (roomNumber == 22)
			update_22_pre();
		else if (roomNumber == 23)
			update_23_pre();
		else if (roomNumber == 24)
			update_24_pre();
		else if (roomNumber == 26)
			update_26_pre();
		else if (roomNumber == 27)
			update_27_pre();
		else if (roomNumber == 29)
			update_29_pre();
		else if (roomNumber == 30)
			update_30_pre();
		else if (roomNumber == 31)
			update_31_pre();
		else if (roomNumber == 34)
			update_34_pre();
		else if (roomNumber == 35)
			update_35_pre();
	} else if (num_ejec == 5) {
		if (roomNumber == 49)
			update_49_pre();
		else if (roomNumber == 53)
			update_53_pre();
		else if (roomNumber == 54)
			update_54_pre();
		else if (roomNumber == 56)
			update_56_pre();
	} else if (num_ejec == 6) {
		if (roomNumber == 102)
			update_pendulo();
		else if (roomNumber == 58)
			update_58_pre();
		else if (roomNumber == 59)
			update_59_pre();
		else if (roomNumber == 60)
			update_60_pre();
	}
}

void DrasculaEngine::update_1_pre() {
	int cambio_col_antes = cambio_de_color;

	if (hare_x > 98 && hare_x < 153)
		cambio_de_color = 1;
	else
		cambio_de_color = 0;

	if (cambio_col_antes != cambio_de_color && cambio_de_color == 1)
		hare_oscuro();
	if (cambio_col_antes != cambio_de_color && cambio_de_color == 0)
		hare_claro();

	if (flags[8] == 0)
		copyBackground(2, 158, 208, 67, 27, 40, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_2(){
	int pos_murci[6];
	int diferencia;
	int murci_x[] = {0, 38, 76, 114, 152, 190, 228, 266,
					0, 38, 76, 114, 152, 190, 228, 266,
					0, 38, 76, 114, 152, 190,
					0, 48, 96, 144, 192, 240,
					30, 88, 146, 204, 262,
					88, 146, 204, 262,
					88, 146, 204, 262};

	int murci_y[] = {179, 179, 179, 179, 179, 179, 179, 179,
					158, 158, 158, 158, 158, 158, 158, 158,
					137, 137, 137, 137, 137, 137,
					115, 115, 115, 115, 115, 115,
					78, 78, 78, 78, 78,
					41, 41, 41, 41,
					4, 4, 4, 4};

	if (frame_murcielago == 41)
		frame_murcielago = 0;

	pos_murci[0] = murci_x[frame_murcielago];
	pos_murci[1] = murci_y[frame_murcielago];

	if (frame_murcielago < 22) {
		pos_murci[4] = 37;
		pos_murci[5] = 21;
	} else if (frame_murcielago > 27) {
		pos_murci[4] = 57;
		pos_murci[5] = 36;
	} else {
		pos_murci[4] = 47;
		pos_murci[5] = 22;
	}

	pos_murci[2] = 239;
	pos_murci[3] = 19;

	copyRectClip(pos_murci, dir_dibujo3, dir_zona_pantalla);
	diferencia = vez() - conta_ciego_vez;
	if (diferencia >= 6) {
		frame_murcielago++;
		conta_ciego_vez = vez();
	}

	copyRect(29, 37, 58, 114, 57, 39, dir_dibujo3, dir_zona_pantalla);
	mapa();
}

void DrasculaEngine::update_3_pre() {
	if (flags[3] == 1)
		copyBackground(258, 110, 85, 44, 23, 53, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_3() {
	if (hare_y + alto_hare < 118)
		copyRect(129, 110, 194, 36, 126, 88, dir_dibujo3, dir_zona_pantalla);
	copyRect(47, 57, 277, 143, 43, 50, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_4() {
	int cambio_col_antes = cambio_de_color;
	if (hare_x > 190)
		cambio_de_color = 1;
	else
		cambio_de_color = 0;

	if (cambio_col_antes != cambio_de_color && cambio_de_color == 1)
		hare_oscuro();
	if (cambio_col_antes != cambio_de_color && cambio_de_color == 0)
		hare_claro();
}

void DrasculaEngine::update_5_pre(){
	if (flags[8] == 0)
		copyBackground(256, 152, 208, 67, 27, 40, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_5() {
	copyRect(114, 130, 211, 87, 109, 69, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_6_pre() {
	int cambio_col_antes = cambio_de_color;

	if ((hare_x > 149 && hare_y + alto_hare > 160 && hare_x < 220 && hare_y + alto_hare < 188) ||
			(hare_x > 75 && hare_y + alto_hare > 183 && hare_x < 145))
		cambio_de_color = 0;
	else
		cambio_de_color = 1;

	if (cambio_col_antes != cambio_de_color && cambio_de_color == 1)
		hare_oscuro();
	if (cambio_col_antes != cambio_de_color && cambio_de_color == 0)
		hare_claro();

	if (flags[1] == 0)
		copyBackground(97, 117, 34, 148, 36, 31, dir_dibujo3, dir_zona_pantalla);
	if (flags[0] == 0)
		copyBackground(3, 103, 185, 69, 23, 76, dir_dibujo3, dir_zona_pantalla);
	if (flags[2] == 0)
		copyBackground(28, 100, 219, 72, 64, 97, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_7_pre() {
	if (flags[35] == 0)
		copyBackground(1, 72, 158, 162, 19, 12, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_9_pre() {
	int ciego_x[] = {26, 68, 110, 152, 194, 236, 278, 26, 68};
	int ciego_y[] = {51, 51, 51, 51, 51, 51, 51, 127, 127};
	int diferencia;

	copyRect(ciego_x[frame_ciego], ciego_y[frame_ciego], 122, 57, 41, 72, dir_dibujo3, dir_zona_pantalla);
	if (flags[9] == 0) {
		diferencia = vez() - conta_ciego_vez;
		if (diferencia >= 11) {
			frame_ciego++;
			conta_ciego_vez = vez();
		}
		if (frame_ciego == 9)
			frame_ciego = 0;
	} else
		frame_ciego = 3;
}

void DrasculaEngine::update_12_pre() {
	if (flags[16] == 0)
		copyBackground(1, 131, 106, 117, 55, 68, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_13() {
	if (hare_x > 55 && flags[3] == 0)
		animation_6_3();
	if (flags[1] == 0)
		copyRect(185, 110, 121, 65, 67, 88, dir_dibujo3, dir_zona_pantalla);
	if (flags[2] == 0)
		copyRect(185, 21, 121, 63, 67, 88, dir_dibujo3, dir_zona_pantalla);
	copyRect(3, 127, 99, 102, 181, 71, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_14_pre() {
	int velas_y[] = {158, 172, 186};
	int cirio_x[] = {14, 19, 24};
	int pianista_x[] = {1, 91, 61, 31, 91, 31, 1, 61, 31};
	int borracho_x[] = {1, 42, 83, 124, 165, 206, 247, 1};
	int diferencia;

	copyBackground(123, velas_y[frame_velas], 142, 14, 39, 13, dir_dibujo3, dir_zona_pantalla);
	copyBackground(cirio_x[frame_velas], 146, 311, 80, 4, 8, dir_dibujo3, dir_zona_pantalla);

	if (parpadeo == 5)
		copyBackground(1, 149, 127, 52, 9, 5, dir_dibujo3, dir_zona_pantalla);
	if (hare_x > 101 && hare_x < 155)
		copyBackground(31, 138, 178, 51, 18, 16, dir_dibujo3, dir_zona_pantalla);
	if (flags[11] == 0)
		copyBackground(pianista_x[frame_piano], 157, 245, 130, 29, 42, dir_dibujo3, dir_zona_pantalla);
	else if (flags[5] == 0)
		copyBackground(145, 139, 228, 112, 47, 60, dir_hare_dch, dir_zona_pantalla);
	else
		copyBackground(165, 140, 229, 117, 43, 59, dir_dibujo3, dir_zona_pantalla);

	if (flags[12] == 1)
		copyBackground(borracho_x[frame_borracho], 82, 170, 50, 40, 53, dir_dibujo3, dir_zona_pantalla);
	diferencia = vez() - conta_ciego_vez;
	if (diferencia > 6) {
		if (flags[12] == 1) {
			frame_borracho++;
			if (frame_borracho == 8) {
				frame_borracho = 0;
				flags[12] = 0;
			}
		} else if ((_rnd->getRandomNumber(94) == 15) && (flags[13] == 0))
			flags[12] = 1;

		frame_velas++;
		if (frame_velas == 3)
			frame_velas = 0;
		frame_piano++;
		if (frame_piano == 9)
			frame_piano = 0;
		parpadeo = _rnd->getRandomNumber(10);
		conta_ciego_vez = vez();
	}
}

void DrasculaEngine::update_15() {
	copyRect(1, 154, 83, 122, 131, 44, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_16_pre() {
	if (flags[17] == 0)
		copyBackground(1, 103, 24, 72, 33, 95, dir_dibujo3, dir_zona_pantalla);
	if (flags[19] == 1)
		copyBackground(37, 151, 224, 115, 56, 47, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_17_pre() {
	if (flags[15] == 1)
		copyBackground(1, 135, 108, 65, 44, 63, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_17() {
	copyRect(48, 135, 78, 139, 80, 30, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_18_pre() {
	int diferencia;
	int ronquido_x[] = {95, 136, 95, 136, 95, 95, 95, 95, 136, 95, 95, 95, 95, 95, 95, 95};
	int ronquido_y[] = {18, 18, 56, 56, 94, 94, 94, 94, 94, 18, 18, 18, 18, 18, 18, 18};

	if (flags[21] == 0) {
		copyBackground(1, 69, 120, 58, 56, 61, dir_dibujo3, dir_zona_pantalla);
		copyBackground(ronquido_x[frame_ronquido], ronquido_y[frame_ronquido], 124, 59, 40, 37, dir_dibujo3, dir_zona_pantalla);
	} else
		pon_vb();

	diferencia = vez() - conta_ciego_vez;
	if (diferencia > 9) {
		frame_ronquido++;
		if (frame_ronquido == 16)
			frame_ronquido = 0;
		conta_ciego_vez = vez();
	}
}

void DrasculaEngine::update_18() {
	if (flags[24] == 1)
		copyRect(177, 1, 69, 29, 142, 130, dir_dibujo3, dir_zona_pantalla);
	copyRect(105, 132, 109, 108, 196, 65, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_20() {
	copyRect(1, 137, 106, 121, 213, 61, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_21_pre() {
	if (flags[0] == 1)
		copyBackground(2, 171, 84, 126, 17, 26, dir_dibujo3, dir_zona_pantalla);

	if (flags[10] == 1)
		copyBackground(20, 163, 257, 149, 14, 34, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_22_pre() {
	if (flags[24] == 1)
		copyBackground(2, 187, 107, 106, 62, 12, dir_dibujo3, dir_zona_pantalla);

	if (flags[27] == 0)
		copyBackground(32, 181, 203, 88, 13, 5, dir_dibujo3, dir_zona_pantalla);

	if (flags[26] == 0)
		copyBackground(2, 133, 137, 83, 29, 53, dir_dibujo3, dir_zona_pantalla);
	else
		copyBackground(65, 174, 109, 145, 55, 25, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_23_pre() {
	if (flags[11] == 1 && flags[0] == 0)
		copyBackground(87, 171, 237, 110, 20, 28, dir_dibujo3, dir_zona_pantalla);

	if (flags[0] == 1)
		copyBackground(29, 126, 239, 94, 57, 73, dir_dibujo3, dir_zona_pantalla);

	if (flags[1] == 1)
		copyRect(1, 135, 7, 94, 27, 64, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_24_pre() {
	if (flags[1] == 1)
		copyBackground(1, 163, 225, 124, 12, 36, dir_dibujo3, dir_zona_pantalla);

	if (flags[2] == 1)
		copyBackground(14, 153, 30, 107, 23, 46, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_26_pre() {
	int diferencia;

	if (flags[2] == 1)
		copyBackground(1, 130, 87, 44, 50, 69, dir_dibujo3, dir_zona_pantalla);

	if (flags[12] == 1)
		copyBackground(52, 177, 272, 103, 27, 22, dir_dibujo3, dir_zona_pantalla);

	if (flags[18] == 0)
		copyBackground(80, 133, 199, 95, 50, 66, dir_dibujo3, dir_zona_pantalla);

	if (parpadeo == 5 && flags[18] == 0)
		copyBackground(52, 172, 226, 106, 3, 4, dir_dibujo3, dir_zona_pantalla);

	diferencia = vez() - conta_ciego_vez;
	if (diferencia >= 10) {
		parpadeo = _rnd->getRandomNumber(10);
		conta_ciego_vez = vez();
	}

	if (flags[20] == 1)
		copyBackground(182, 133, 199, 95, 50, 66, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_26() {
	if (flags[29] == 1)
		copyRect(93, 1, hare_x, hare_y, 45, 78, dir_hare_fondo, dir_zona_pantalla);

	copyRect(233, 107, 17, 102, 66, 92, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_27_pre() {
	if (flags[5] == 1)
		copyRect(1, 175, 59, 109, 17, 24, dir_dibujo3, dir_zona_pantalla);

	if (flags[6] == 1)
		copyRect(19, 177, 161, 103, 18, 22, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_27() {
	copyRect(38, 177, 103, 171, 21, 22, dir_dibujo3, dir_zona_pantalla);
	copyRect(60, 162, 228, 156, 18, 37, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_29_pre() {
	if (flags[4] == 1)
		copyBackground(12, 113, 247, 49, 41, 84, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_29() {
	copyRect(1, 180, 150, 126, 10, 17, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_30_pre() {
	if (flags[4] == 1)
		copyBackground(1, 148, 148, 66, 35, 51, dir_dibujo3, dir_zona_pantalla);

	if (flags[16] == 1)
		copyBackground(37, 173, 109, 84, 20, 26, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_31_pre() {
	if (flags[13] == 1)
		copyBackground(1, 163, 116, 41, 61, 36, dir_dibujo3, dir_zona_pantalla);

	if (flags[5] == 1)
		copyBackground(1, 78, 245, 63, 30, 84, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_31() {
	copyRect(63, 190, 223, 157, 17, 9, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_34_pre() {
	if (flags[7] == 1)
		copyBackground(99, 127, 73, 41, 79, 72, dir_dibujo3, dir_zona_pantalla);

	if (flags[8] == 1)
		copyBackground(36, 129, 153, 41, 62, 65, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_34() {
	copyRect(5, 171, 234, 126, 29, 23, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_35_pre() {
	if (flags[14] == 1)
		copyBackground(1, 86, 246, 65, 68, 87, dir_dibujo3, dir_zona_pantalla);

	if (flags[17] == 0 && flags[15] == 1)
		copyBackground(111, 150, 118, 52, 40, 23, dir_dibujo3, dir_zona_pantalla);

	if (flags[17] == 1)
		copyBackground(70, 150, 118, 52, 40, 23, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_35() {
	copyRect(1, 174, 54, 152, 195, 25, dir_dibujo3, dir_zona_pantalla);
}


void DrasculaEngine::update_49_pre() {
	if (flags[6] == 0)
		copyBackground(2, 136, 176, 81, 49, 62, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_50() {
	copyRect(4, 153, 118, 95, 67, 44, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_53_pre() {
	if (flags[1] == 0)
		copyRect(2, 113, 205, 50, 38, 86, dir_dibujo3, dir_zona_pantalla);
	if (flags[2] == 0)
		copyBackground(41, 159, 27, 117, 25, 40, dir_dibujo3, dir_zona_pantalla);
	if (flags[9] == 1)
		copyBackground(67, 184, 56, 93, 32, 15, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_54_pre() {
	if (flags[5] == 1)
		copyBackground(168, 156, 187, 111, 7, 11, dir_dibujo3, dir_zona_pantalla);
	if (flags[12] == 1)
		copyBackground(16, 156, 190, 64, 18, 24, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_56_pre() {
	if (flags[10] == 0)
		copyBackground(2, 126, 42, 67, 57, 67, dir_dibujo3, dir_zona_pantalla);
	if (flags[11] == 1)
		copyBackground(60, 160, 128, 97, 103, 38, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_57() {
	copyRect(7, 113, 166, 61, 62, 82, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_58_pre() {
	if (flags[0] == 0)
		copyBackground(1, 156, 143, 120, 120, 43, dir_dibujo3, dir_zona_pantalla);
	if (flags[1] == 2)
		copyRect(252, 171, 173, 116, 25, 28, dir_dibujo3, dir_zona_pantalla);
	if (flags[1] == 0 && flags[0] == 0)
		copyRect(278, 171, 173, 116, 25, 28, dir_dibujo3, dir_zona_pantalla);
	if (flags[2] == 0) {
		pon_igor();
		pon_dr();
	}
	if (flags[3] == 1)
		copyRect(1, 29, 204, 0, 18, 125, dir_dibujo3, dir_zona_pantalla);
	if (flags[8] == 1)
		copyBackground(20, 60, 30, 64, 46, 95, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_58() {
	if (hare_se_ve == 1)
		copyRect(67, 139, 140, 147, 12, 16, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_59_pre() {
	if (flags[4] == 0)
		copyRect(1, 146, 65, 106, 83, 40, dir_dibujo3, dir_zona_pantalla);
	if (flags[9] == 1) {
		copyBackground(65, 103, 65, 103, 49, 38, dir_dibujo1, dir_zona_pantalla);
		copyRect(1, 105, 65, 103, 49, 38, dir_dibujo3, dir_zona_pantalla);
	}
}

void DrasculaEngine::update_60_pre() {
	int velas_y[] = {158, 172, 186};
	int diferencia;

	if (flags[5] == 0)
		pon_dr();

	copyBackground(123, velas_y[frame_velas], 142, 14, 39, 13, dir_dibujo3, dir_zona_pantalla);

	if (flag_tv == 1)
		copyBackground(114, 158, 8, 30, 8, 23, dir_dibujo3, dir_zona_pantalla);

	diferencia = vez() - conta_ciego_vez;
	parpadeo = _rnd->getRandomNumber(7);
	if (parpadeo == 5 && flag_tv == 0)
		flag_tv = 1;
	else if (parpadeo == 5 && flag_tv == 1)
		flag_tv = 0;
	if (diferencia > 6) {
		frame_velas++;
		if (frame_velas == 3)
			frame_velas = 0;
		conta_ciego_vez = vez();
	}
}

void DrasculaEngine::update_60() {
	if (hare_y - 10 < y_dr && flags[5] == 0)
		pon_dr();
}

void DrasculaEngine::update_61() {
	copyRect(1, 154, 83, 122, 131, 44, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_62_pre() {
	int velas_y[] = { 158, 172, 186 };
	int cirio_x[] = { 14, 19, 24 };
	int pianista_x[] = {1, 91, 61, 31, 91, 31, 1, 61, 31 };
	int borracho_x[] = {1, 42, 83, 124, 165, 206, 247, 1 };
	int diferencia;

	copyBackground(123, velas_y[frame_velas], 142, 14, 39, 13, dir_dibujo3, dir_zona_pantalla);
	copyBackground(cirio_x[frame_velas], 146, 311, 80, 4, 8, dir_dibujo3, dir_zona_pantalla);

	if (parpadeo == 5)
		copyBackground(1, 149, 127, 52, 9, 5, dir_dibujo3, dir_zona_pantalla);

	if (hare_x > 101 && hare_x < 155)
		copyBackground(31, 138, 178, 51, 18, 16, dir_dibujo3, dir_zona_pantalla);

	if (flags[11] == 0)
		copyBackground(pianista_x[frame_piano], 157, 245, 130, 29, 42, dir_dibujo3, dir_zona_pantalla);
	else if (flags[5] == 0)
		copyBackground(145, 139, 228, 112, 47, 60, dir_hare_dch, dir_zona_pantalla);
	else
		copyBackground(165, 140, 229, 117, 43, 59, dir_dibujo3, dir_zona_pantalla);

	if (flags[12] == 1)
		copyBackground(borracho_x[frame_borracho], 82, 170, 50, 40, 53, dir_dibujo3, dir_zona_pantalla);

	diferencia = vez() - conta_ciego_vez;
	if (diferencia > 6) {
		if (flags[12] == 1) {
			frame_borracho++;
			if (frame_borracho == 8) {
				frame_borracho = 0;
				flags[12] = 0;
			}
		} else if ((_rnd->getRandomNumber(94) == 15) && (flags[13] == 0))
			flags[12] = 1;

		frame_velas++;
		if (frame_velas == 3)
			frame_velas = 0;
		frame_piano++;
		if (frame_piano == 9)
			frame_piano = 0;
		parpadeo = _rnd->getRandomNumber(10);
		conta_ciego_vez = vez();
	}
}

void DrasculaEngine::update_62() {
	int borracho_x[] = { 1, 42, 83, 124, 165, 206, 247, 1 };

	copyRect(1, 1, 0, 0, 62, 142, dir_dibujo2, dir_zona_pantalla);

	if (hare_y + alto_hare < 89) {
		copyRect(205, 1, 180, 9, 82, 80, dir_dibujo3, dir_zona_pantalla);
		copyBackground(borracho_x[frame_borracho], 82, 170, 50, 40, 53, dir_dibujo3, dir_zona_pantalla);
	}
}

void DrasculaEngine::update_63() {
	copyRect(1, 154, 83, 122, 131, 44, dir_dibujo3, dir_zona_pantalla);
}

void DrasculaEngine::update_pendulo() {
	int pendulo_x[] = {40, 96, 152, 208, 264, 40, 96, 152, 208, 208, 152, 264, 40, 96, 152, 208, 264};
	int diferencia;

	if (frame_pen <= 4)
		dir_pendulo = dir_dibujo3;
	else if (frame_pen <= 11)
		dir_pendulo = dir_hare_dch;
	else
		dir_pendulo = dir_hare_frente;

	copyBackground(pendulo_x[frame_pen], 19, 152, 0, 55, 125, dir_pendulo, dir_zona_pantalla);

	if (flags[1] == 2)
		copyRect(18, 145, 145, 105, 25, 29, dir_dibujo3, dir_zona_pantalla);

	if (flags[1] == 0)
		copyRect(44, 145, 145, 105, 25, 29, dir_dibujo3, dir_zona_pantalla);

	diferencia = vez() - conta_ciego_vez;
	if (diferencia > 8) {
		frame_pen++;
		if (frame_pen == 17)
			frame_pen = 0;
		conta_ciego_vez = vez();
	}
}

} // End of namespace Drascula
