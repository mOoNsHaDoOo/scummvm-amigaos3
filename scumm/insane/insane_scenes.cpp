/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2004 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include "stdafx.h"

#include "base/engine.h"

#include "common/config-manager.h"

#include "scumm/scumm.h"
#include "scumm/sound.h"

#include "scumm/insane/insane.h"

namespace Scumm {

void Insane::runScene(int arraynum) {
	//	  procPtr5 = &procPtr5Body;
	//	  procPtr6 = &procPtr6Body;
	//	  procIact = &handleIact;
	//	  ptrMainLoop = &ptrMainLoopBody;

	_insaneIsRunning = true;
	_player = new SmushPlayer(_vm, _speed);
	_player->insanity(true);

	_numberArray = arraynum;

	// set4Values()
	_val109w = 114;
	_val110w = 256;
	_val111w = 4;
	_val112w = 256;
	// set1Value()
	_val113d = 0;
	// zeroValues1()
	_objArray2Idx = 0;
	_objArray2Idx2 = 0;
	// zeroValues2()
	_objArray1Idx = 0;
	_objArray1Idx2 = 0;
	// zeroValues3()
	_currScenePropIdx = 0;
	_currScenePropSubIdx = 0;
	_currTrsMsg = 0;

	smush_proc41();
	smush_warpMouse(160, 100, -1);
	putActors();
	readState();
	_val10b = _val50d; // FIXME: seems to be unused
	setTrsFile(_trsFilePtr); // FIXME: we don't need it

	debug(0, "INSANE Arg: %d", readArray(_numberArray, 0));

	switch (readArray(_numberArray, 0)) {
	case 1:
		initScene(1);
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		startVideo("minedriv.san", 1, 32, 12, 0);
		break;
	case 2:
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		_val8d = readArray(_numberArray, 2);
		if (_val55d) {
			initScene(5);
			startVideo("tovista2.san", 1, 32, 12, 0);
		} else if (_val56d) {
			initScene(5);
			startVideo("tovista2.san", 1, 32, 12, 0, _smush_tovista2Flu, 60);
		} else {
			initScene(4);
			startVideo("tovista1.san", 1, 32, 12, 0);
		}
		break;
	case 3:
		setupValues();
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		_val8d = readArray(_numberArray, 2);
		if (_val55d) {
			initScene(6);
			startVideo("toranch.san", 1, 32, 12, 0, _smush_toranchFlu, 300);
		} else if (_val56d) {
			initScene(6);
			startVideo("toranch.san", 1, 32, 12, 0, _smush_toranchFlu, 240);
		} else {
			initScene(6);
			startVideo("toranch.san", 1, 32, 12, 0);
		}
		break;
	case 4:
		_firstBattle = true;
		_currEnemy = EN_ROTT1;
		initScene(13);
		startVideo("minefite.san", 1, 32, 12, 0);
		break;
	case 5:
		setWordInString(_numberArray, 1, _val54d);
		initScene(24);
		startVideo("rottopen.san", 1, 32, 12, 0);
		break;
	case 6:
		initScene(1);
		setupValues();
		smlayer_setFluPalette(_smush_roadrashRip, 1);
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		startVideo("minedriv.san", 1, 32, 12, 0, _smush_minedrivFlu, 420);
		break;
	case 7:
	case 8:
	case 9:
		break;
	case 10:
		initScene(26);
		setWordInString(_numberArray, 1, _val54d);
		startVideo("credits.san", 1, 32, 12, 0);
	default:
		warning("Unknown FT_INSANE mode %d", readArray(_numberArray, 0));
		break;
	}

	resetTrsFilePtr(); // FIXME: we don't need it
	smush_proc39();
	putActors();
	smush_proc40();
	_vm->_sound->pauseSounds(0); // IMUSE_Resume();
	_enemy[EN_ROTT3].maxdamage = 120;

	_insaneIsRunning = false;

	setWordInString(_numberArray, 50, _actor[0].inventory[INV_CHAIN]);
	setWordInString(_numberArray, 51, _actor[0].inventory[INV_CHAINSAW]);
	setWordInString(_numberArray, 52, _actor[0].inventory[INV_MACE]);
	setWordInString(_numberArray, 53, _actor[0].inventory[INV_2X4]);
	setWordInString(_numberArray, 54, _actor[0].inventory[INV_WRENCH]);
	setWordInString(_numberArray, 55, _actor[0].inventory[INV_DUST]);
	setWordInString(_numberArray, 337, _enemy[EN_TORQUE].field_8);
	setWordInString(_numberArray, 329, _enemy[EN_ROTT1].field_8);
	setWordInString(_numberArray, 330, _enemy[EN_ROTT2].field_8);
	setWordInString(_numberArray, 331, _enemy[EN_ROTT3].field_8);
	setWordInString(_numberArray, 332, _enemy[EN_VULTF1].field_8);
	setWordInString(_numberArray, 333, _enemy[EN_VULTM1].field_8);
	setWordInString(_numberArray, 334, _enemy[EN_VULTF2].field_8);
	setWordInString(_numberArray, 335, _enemy[EN_VULTM2].field_8);
	setWordInString(_numberArray, 336, _enemy[EN_CAVEFISH].field_8);
	setWordInString(_numberArray, 339, _enemy[EN_VULTF2].field_10);
	setWordInString(_numberArray, 56, _enemy[EN_CAVEFISH].field_10);
	setWordInString(_numberArray, 340, _enemy[EN_VULTM2].field_10);
	// insane_unlock(); // FIXME
	_vm->_sound->stopAllSounds(); // IMUSE_StopAllSounds();
	if (_memoryAllocatedNotOK) {
		error("Memory Alloc Error in Mineroad (Heap Size?)");
	}
	
	delete _player;
}

int Insane::initScene(int sceneId) {
	debug(0, "initScene(%d)", sceneId);

	if (_needSceneSwitch)
		return 1;

	stopSceneSounds(_currSceneId); // do it for previous scene
	loadSceneData(sceneId, 0, 1);
	if (loadSceneData(sceneId, 0, 2)) {
		setSceneCostumes(sceneId);
		_sceneData2Loaded = 0;
		_sceneData1Loaded = 0;
	} else
		_sceneData2Loaded = 1;

	_currSceneId = sceneId;
	return 1;
}

void Insane::stopSceneSounds(int sceneId) {
	int flag = 0;

	debug(0, "stopSceneSounds(%d)", sceneId);

	switch (sceneId) {
	case 1:
		smlayer_stopSound(88);
		smlayer_stopSound(86);
		smlayer_stopSound(87);
		flag = 1;
		break;
	case 18:
	case 19:
		smlayer_stopSound(88);
		flag = 1;
		break;
	case 17:
		smlayer_stopSound(88);
		smlayer_stopSound(94);
		flag = 1;
		break;
	case 2:
	case 7:
	case 8:
		flag = 1;
		break;
	case 3:
	case 21:
		flag = 1;
		// break is omittted intentionally
	case 13:
		if (_actor[0].runningSound != 0)
			smlayer_stopSound(_actor[0].runningSound);
		_actor[0].runningSound = 0;
	
		if (_actor[1].runningSound != 0)
			smlayer_stopSound(_actor[1].runningSound);
		_actor[1].runningSound = 0;
	
		if (_currScenePropIdx != 0)
			shutCurrentScene();
	
		_currScenePropSubIdx = 0;
		_currTrsMsg = 0;
		_actor[0].defunct = 0;
		_actor[0].scenePropSubIdx = 0;
		_actor[0].field_54 = 0;
		_actor[1].defunct = 0;
		_actor[1].scenePropSubIdx = 0;
		_actor[1].field_54 = 0;
		smlayer_stopSound(89);
		smlayer_stopSound(90);
		smlayer_stopSound(91);
		smlayer_stopSound(92);
		smlayer_stopSound(93);
		smlayer_stopSound(95);
		smlayer_stopSound(87);
		break;
	case 4:
	case 5:
	case 6:
		smlayer_stopSound(88);
		smlayer_stopSound(86);
		flag = 1;
		break;
	case 24:
		smlayer_stopSound(90);
		break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 20:
	case 22:
	case 23:
		break;
	}
	smush_proc39();
	if (!flag)
		return;

	smlayer_setActorCostume(0, 2, 0);
	smlayer_setActorCostume(0, 0, 0);
	smlayer_setActorCostume(0, 1, 0);
	smlayer_setActorCostume(1, 2, 0);
	smlayer_setActorCostume(1, 0, 0);
	smlayer_setActorCostume(1, 1, 0);
	
	return;
}

void Insane::shutCurrentScene(void) {
	debug(0, "shutCurrentScene()");

	_currScenePropIdx = 0;
	_currTrsMsg = 0;
	_currScenePropSubIdx = 0;
	_actor[1].scenePropSubIdx = 0;
	_actor[1].defunct = 0;
	
	if (_actor[1].runningSound != 0) {
		smlayer_stopSound(_actor[1].runningSound);
		_actor[1].runningSound = 0;
	}

	_actor[0].scenePropSubIdx = 0;
	_actor[0].defunct = 0;

	if (_actor[0].runningSound != 0) {
		smlayer_stopSound(_actor[0].runningSound);
		_actor[0].runningSound = 0;
	}

	_battleScene = true;
}


// insane_loadSceneData1 & insane_loadSceneData2
int Insane::loadSceneData(int scene, int flag, int phase) {
	int retvalue = 1;

	debug(0, "Insane::loadSceneData(%d, %d, %d)", scene, flag, phase);
	//if (phase == 1) /// FIXME
	//	insane_unlock();
	switch (scene) {
	case 1:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadSound(86, flag, phase);
		smlayer_loadSound(87, flag, phase);
		smlayer_loadCostume(10, phase);
		break;
	case 4:
	case 5:
	case 6:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadCostume(11, phase);
		break;
	case 3:
	case 13:
		switch(_currEnemy) {
		case EN_TORQUE:
			smlayer_loadSound(59, flag, phase);
			smlayer_loadSound(93, flag, phase);
			smlayer_loadCostume(57, phase);
			smlayer_loadCostume(37, phase);
			break;
		case EN_ROTT1:
			smlayer_loadSound(201, flag, phase);
			smlayer_loadSound(194, flag, phase);
			smlayer_loadSound(195, flag, phase);
			smlayer_loadSound(199, flag, phase);
			smlayer_loadSound(205, flag, phase);
			smlayer_loadSound(212, flag, phase);
			smlayer_loadSound(198, flag, phase);
			smlayer_loadSound(203, flag, phase);
			smlayer_loadSound(213, flag, phase);
			smlayer_loadSound(215, flag, phase);
			smlayer_loadSound(216, flag, phase);
			smlayer_loadSound(217, flag, phase);
			smlayer_loadSound(218, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(26, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(27, phase);
			break;
		case EN_ROTT2:
			smlayer_loadSound(242, flag, phase);
			smlayer_loadSound(244, flag, phase);
			smlayer_loadSound(236, flag, phase);
			smlayer_loadSound(238, flag, phase);
			smlayer_loadSound(239, flag, phase);
			smlayer_loadSound(240, flag, phase);
			smlayer_loadSound(258, flag, phase);
			smlayer_loadSound(259, flag, phase);
			smlayer_loadSound(260, flag, phase);
			smlayer_loadSound(243, flag, phase);
			smlayer_loadSound(244, flag, phase);
			smlayer_loadSound(245, flag, phase);
			smlayer_loadSound(246, flag, phase);
			smlayer_loadSound(233, flag, phase);
			smlayer_loadSound(234, flag, phase);
			smlayer_loadSound(241, flag, phase);
			smlayer_loadSound(242, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(28, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(42, phase);
			break;
		case EN_ROTT3:
			smlayer_loadSound(223, flag, phase);
			smlayer_loadSound(224, flag, phase);
			smlayer_loadSound(225, flag, phase);
			smlayer_loadSound(226, flag, phase);
			smlayer_loadSound(228, flag, phase);
			smlayer_loadSound(229, flag, phase);
			smlayer_loadSound(230, flag, phase);
			smlayer_loadSound(232, flag, phase);
			smlayer_loadSound(220, flag, phase);
			smlayer_loadSound(221, flag, phase);
			smlayer_loadSound(222, flag, phase);
			smlayer_loadSound(90, flag, phase);
			smlayer_loadCostume(15, phase);
			smlayer_loadCostume(16, phase);
			smlayer_loadCostume(17, phase);
			smlayer_loadCostume(43, phase);
			smlayer_loadCostume(47, phase);
			break;
		case EN_VULTF1:
			smlayer_loadSound(282, flag, phase);
			smlayer_loadSound(283, flag, phase);
			smlayer_loadSound(284, flag, phase);
			smlayer_loadSound(285, flag, phase);
			smlayer_loadSound(286, flag, phase);
			smlayer_loadSound(287, flag, phase);
			smlayer_loadSound(279, flag, phase);
			smlayer_loadSound(280, flag, phase);
			smlayer_loadSound(281, flag, phase);
			smlayer_loadSound(277, flag, phase);
			smlayer_loadSound(288, flag, phase);
			smlayer_loadSound(278, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(29, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(37, phase);
			break;
		case EN_VULTM1:
			smlayer_loadSound(160, flag, phase);
			smlayer_loadSound(161, flag, phase);
			smlayer_loadSound(174, flag, phase);
			smlayer_loadSound(167, flag, phase);
			smlayer_loadSound(163, flag, phase);
			smlayer_loadSound(164, flag, phase);
			smlayer_loadSound(170, flag, phase);
			smlayer_loadSound(166, flag, phase);
			smlayer_loadSound(175, flag, phase);
			smlayer_loadSound(162, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(30, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(36, phase);
			break;
		case EN_VULTF2:
			smlayer_loadSound(263, flag, phase);
			smlayer_loadSound(264, flag, phase);
			smlayer_loadSound(265, flag, phase);
			smlayer_loadSound(266, flag, phase);
			smlayer_loadSound(267, flag, phase);
			smlayer_loadSound(268, flag, phase);
			smlayer_loadSound(270, flag, phase);
			smlayer_loadSound(271, flag, phase);
			smlayer_loadSound(275, flag, phase);
			smlayer_loadSound(276, flag, phase);
			smlayer_loadSound(261, flag, phase);
			smlayer_loadSound(262, flag, phase);
			smlayer_loadSound(263, flag, phase);
			smlayer_loadSound(274, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(31, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(35, phase);
			smlayer_loadCostume(46, phase);
			break;
		case EN_VULTM2:
			smlayer_loadSound(179, flag, phase);
			smlayer_loadSound(183, flag, phase);
			smlayer_loadSound(184, flag, phase);
			smlayer_loadSound(186, flag, phase);
			smlayer_loadSound(191, flag, phase);
			smlayer_loadSound(192, flag, phase);
			smlayer_loadSound(180, flag, phase);
			smlayer_loadSound(101, flag, phase);
			smlayer_loadSound(289, flag, phase);
			smlayer_loadSound(177, flag, phase);
			smlayer_loadSound(178, flag, phase);
			smlayer_loadSound(290, flag, phase);
			smlayer_loadSound(102, flag, phase);
			smlayer_loadSound(91, flag, phase);
			smlayer_loadCostume(34, phase);
			smlayer_loadCostume(33, phase);
			smlayer_loadCostume(32, phase);
			smlayer_loadCostume(44, phase);
			smlayer_loadCostume(45, phase);
			break;
		case EN_CAVEFISH:
			smlayer_loadSound(291, flag, phase);
			smlayer_loadSound(100, flag, phase);
			smlayer_loadSound(92, flag, phase);
			smlayer_loadCostume(39, phase);
			smlayer_loadCostume(40, phase);
			smlayer_loadCostume(41, phase);
			break;
		default:
			retvalue = 0;
			break;
		}
		smlayer_loadSound(64, flag, phase);
		smlayer_loadSound(65, flag, phase);
		smlayer_loadSound(66, flag, phase);
		smlayer_loadSound(67, flag, phase);
		smlayer_loadSound(68, flag, phase);
		smlayer_loadSound(69, flag, phase);
		smlayer_loadSound(70, flag, phase);
		smlayer_loadSound(71, flag, phase);
		smlayer_loadSound(72, flag, phase);
		smlayer_loadSound(73, flag, phase);
		smlayer_loadSound(74, flag, phase);
		smlayer_loadSound(75, flag, phase);
		smlayer_loadSound(76, flag, phase);
		smlayer_loadSound(77, flag, phase);
		smlayer_loadSound(78, flag, phase);
		smlayer_loadSound(79, flag, phase);
		smlayer_loadSound(80, flag, phase);
		smlayer_loadSound(81, flag, phase);
		smlayer_loadSound(82, flag, phase);
		smlayer_loadSound(83, flag, phase);
		smlayer_loadSound(84, flag, phase);
		smlayer_loadSound(85, flag, phase);
		smlayer_loadSound(86, flag, phase);
		smlayer_loadSound(87, flag, phase);
		smlayer_loadSound(62, flag, phase);
		smlayer_loadSound(63, flag, phase);
		smlayer_loadSound(60, flag, phase);
		smlayer_loadSound(61, flag, phase);
		smlayer_loadSound(315, flag, phase);
		smlayer_loadSound(316, flag, phase);
		smlayer_loadSound(317, flag, phase);
		smlayer_loadSound(98, flag, phase);
		smlayer_loadSound(318, flag, phase);
		smlayer_loadSound(96, flag, phase);
		smlayer_loadSound(97, flag, phase);
		smlayer_loadSound(95, flag, phase);
		smlayer_loadSound(89, flag, phase);
		smlayer_loadCostume(12, phase);
		smlayer_loadCostume(13, phase);
		smlayer_loadCostume(14, phase);
		smlayer_loadCostume(18, phase);
		smlayer_loadCostume(22, phase);
		smlayer_loadCostume(19, phase);
		smlayer_loadCostume(38, phase);
		smlayer_loadCostume(20, phase);
		smlayer_loadCostume(21, phase);
		smlayer_loadCostume(23, phase);
		smlayer_loadCostume(24, phase);
		smlayer_loadCostume(25, phase);
		break;
	case 21:
	case 24:
	case 25:
		smlayer_loadSound(223, flag, phase);
		smlayer_loadSound(224, flag, phase);
		smlayer_loadSound(225, flag, phase);
		smlayer_loadSound(226, flag, phase);
		smlayer_loadSound(228, flag, phase);
		smlayer_loadSound(229, flag, phase);
		smlayer_loadSound(230, flag, phase);
		smlayer_loadSound(232, flag, phase);
		smlayer_loadSound(90, flag, phase);
		smlayer_loadCostume(15, phase);
		smlayer_loadCostume(16, phase);
		smlayer_loadCostume(17, phase);
		smlayer_loadCostume(43, phase);
		smlayer_loadSound(62, flag, phase);
		smlayer_loadSound(63, flag, phase);
		smlayer_loadSound(60, flag, phase);
		smlayer_loadSound(61, flag, phase);
		smlayer_loadSound(315, flag, phase);
		smlayer_loadSound(316, flag, phase);
		smlayer_loadSound(317, flag, phase);
		smlayer_loadSound(98, flag, phase);
		smlayer_loadSound(318, flag, phase);
		smlayer_loadSound(96, flag, phase);
		smlayer_loadSound(97, flag, phase);
		smlayer_loadSound(95, flag, phase);
		smlayer_loadSound(89, flag, phase);
		smlayer_loadCostume(12, phase);
		smlayer_loadCostume(13, phase);
		smlayer_loadCostume(14, phase);
		smlayer_loadCostume(18, phase);
		smlayer_loadCostume(22, phase);
		break;
	case 17:
		smlayer_loadSound(88, flag, phase);
		smlayer_loadSound(94, flag, phase);
		break;
	case 2:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 18:
	case 19:
	case 20:
	case 22:
	case 23:
		break;
	default:
		retvalue = 0;
	}
	if (phase == 1) {
		_sceneData1Loaded = 1;
		_val11d = 0;
	}
	return retvalue;
}

void Insane::setSceneCostumes(int sceneId) {
	debug(0, "Insane::setSceneCostumes(%d)", sceneId);

	switch (sceneId) {
	case 1:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		setupValues();
		return;
		break;
	case 17:
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
		setupValues();
		return;
		break;
	case 2:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 10));
		setupValues();
		return;
		break;
	case 13:
		setEnemyCostumes();
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		return;
		break;
	case 21:
		_currEnemy = EN_ROTT3; // PATCH
		setEnemyCostumes();
		_actor[1].y = 200;
		smlayer_setFluPalette(_smush_roadrashRip, 0);
		return;
		break;
	case 4:
	case 5:
	case 6:
		smlayer_setActorCostume(0, 2, readArray(_numberArray, 11));
		smlayer_putActor(0, 2, _actor[0].x, _actor[0].y1+190, _smlayer_room2);
		setupValues();
		return;
		break;
	case 7:
	case 8:
		setWordInString(_numberArray, 4, 0);
		return;
	}
}

void Insane::setEnemyCostumes(void) {
	int i;

	debug(0, "setEnemyCostumes(%d)", _currEnemy);

	smlayer_setActorCostume(0, 2, readArray(_numberArray, 12));
	smlayer_setActorCostume(0, 0, readArray(_numberArray, 14));
	smlayer_setActorCostume(0, 1, readArray(_numberArray, 13));
	smlayer_setActorLayer(0, 1, 1);
	smlayer_setActorLayer(0, 2, 5);
	smlayer_setActorLayer(0, 0, 10);
	smlayer_putActor(0, 2, _actor[0].x+11, _actor[0].y1+102, _smlayer_room2);
	smlayer_putActor(0, 1, _actor[0].x, _actor[0].y1+200, _smlayer_room2);
	smlayer_putActor(0, 0, _actor[0].x, _actor[0].y1+200, _smlayer_room2);
	
	if (_currEnemy == EN_CAVEFISH) {
		smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 0;
		_actor[1].act[0].room = 0;
		_actor[1].act[2].animTilt = 1;
		_actor[1].field_8 = 98;
		_actor[1].act[2].state = 98;
		_actor[1].act[0].state = 98;
		_actor[1].act[1].state = 98;
	
		smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].tilt - 17, 
						 _actor[1].y + _actor[1].y1 - 98, _smlayer_room2);
	} else if (_currEnemy == EN_TORQUE) {
		smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 0;
		_actor[1].act[0].room = 0;
		_actor[1].field_8 = 1;
		_actor[1].act[2].state = 1;
		_actor[1].act[0].state = 1;
		_actor[1].act[1].state = 1;
		smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].tilt - 17, 
						 _actor[1].y + _actor[1].y1 - 98, _smlayer_room2);
	} else {
		_actor[1].act[2].room = 1;
		_actor[1].act[1].room = 1;
		_actor[1].act[0].room = 1;
	
		if (_enemy[_currEnemy].costume4)
			smlayer_setActorCostume(1, 2, readArray(_numberArray, _enemy[_currEnemy].costume4));
	
		if (_enemy[_currEnemy].costume5)
			smlayer_setActorCostume(1, 0, readArray(_numberArray, _enemy[_currEnemy].costume5));
	
		if (_enemy[_currEnemy].costume6)
			smlayer_setActorCostume(1, 1, readArray(_numberArray, _enemy[_currEnemy].costume6));
	
		_actor[1].field_8 = 1;
		_actor[1].act[2].state = 1;
		_actor[1].act[0].state = 1;
		_actor[1].act[1].state = 1;
	
		if (_actor[1].act[2].room != 0)
			smlayer_putActor(1, 2, _actor[1].x + _actor[1].act[2].tilt - 17, 
							 _actor[1].y + _actor[1].y1 - 98, 
							 _smlayer_room2);
	}
	
	if (_actor[1].act[1].room != 0)
		smlayer_putActor(1, 1, _actor[1].x, _actor[1].y + _actor[1].y1,
						 _smlayer_room2);
	
	if (_actor[1].act[0].room != 0)
		smlayer_putActor(1, 0, _actor[1].x, _actor[1].y + _actor[1].y1, 
						 _smlayer_room2);
	
	smlayer_setActorLayer(1, 1, 1);
	smlayer_setActorLayer(1, 2, 5);
	smlayer_setActorLayer(1, 0, 10);
	
	_actor[1].damage = 0;
	_actor[1].x = 250;
	_actor[1].y = 300;
	_actor[1].cursorX = 0;
	_actor[1].tilt = 0;
	_actor[1].weapon = -1;
	_actor[1].weaponClass = 2;
	_enemy[_currEnemy].field_8++;
	_actor[1].maxdamage = _enemy[_currEnemy].maxdamage;
	_actor[1].enemyHandler = _enemy[_currEnemy].handler;
	_actor[1].animWeaponClass = 0;
	for (i = 0; i < 8; i++)
		_actor[1].inventory[i] = 0;
	_actor[0].damage = 0;
	_actor[0].x = 100;
	_actor[0].y = 200;
	_actor[0].weapon = INV_HAND;
	_actor[0].weaponClass = 2;
	_actor[0].animWeaponClass = 0;
	_actor[0].field_34 = 2;
	_actor[0].field_38 = 0;
	_actor[0].tilt = 0;
	_actor[0].field_8 = 1;
	_actor[0].act[2].state = 1;
	_actor[0].act[2].animTilt = 1;
	_actor[0].act[0].state = 0;
	_actor[0].act[1].state = 1;
	_actor[0].act[2].room = 1;
	_actor[0].act[1].room = 1;
	_actor[0].act[0].room = 1;
	_actor[0].cursorX = 0;
	_actor[0].defunct = 0;
	_actor[0].scenePropSubIdx = 0;
	_actor[0].field_54 = 0;
	_actor[0].runningSound = 0;
	_actor[0].lost = 0;
	_actor[0].kicking = 0;
	_actor[0].field_44 = 0;
	_actor[1].inventory[_enemy[_currEnemy].weapon] = 1;
	_actor[0].field_44 = 0;
	_actor[0].field_48 = 0;
	_actor[1].defunct = 0;
	_actor[1].scenePropSubIdx = 0;
	_actor[1].field_54 = 0;
	_actor[1].runningSound = 0;
	_actor[1].lost = 0;
	_actor[1].kicking = 0;
	_actor[1].field_44 = 0;
	_actor[1].field_48 = 0;
	if (_enemy[_currEnemy].initializer != -1)
		enemyInitializer(_enemy[_currEnemy].initializer, _actor[1].damage, 
							 _actor[0].damage, _actor[1].probability);

	smush_warpMouse(160, 100, -1);
}

void Insane::procPreRendering(void) {
	_smush_isSanFileSetup = 0; // FIXME: This shouldn't be here

	switchSceneIfNeeded();

	if (_sceneData1Loaded) {
		if (!_keyboardDisable) {
			smush_changeState(1);
			_smush_isPauseImuse = true;
			IMUSE_shutVolume();
			_keyboardDisable = 1;
		}
	} else {
		_val115w = 0;
		if (_keyboardDisable) {
			if (!_val116w) {
				smush_changeState(0);
				_smush_isPauseImuse = false;
				IMUSE_restoreVolume();
			}
			_keyboardDisable = 0;
		}
	}

	_lastKey = getLastKey(1);
}

void Insane::procPostRendering(byte *renderBitmap, int32 codecparam, int32 setupsan12,
							   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	int32 tmpSnd;
	bool needMore = false;

	if(!_keyboardDisable && !_val116w) {
		switch (_currSceneId) {
		case 12:
			postCase11(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 1:
			postCase0(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSfx(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			if(_tiresRustle) {
				if (!smlayer_isSoundRunning(87))
					smlayer_startSfx(87);
			} else {
				smlayer_stopSound(87);
			}
			break;
		case 18:
		case 19:
			postCase17(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			smlayer_stopSound(95);
			smlayer_stopSound(87);
			smlayer_stopSound(88);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSfx(88);
			break;
		case 17:
			postCase16(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSfx(88);
			break;
		case 2:
			postCase1(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 3:
			postCase2(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSfx(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSfx(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			if(!_tiresRustle) {
				smlayer_stopSound(87);
			} else {
				if (!smlayer_isSoundRunning(87))
					smlayer_startSfx(87);
			}
			break;
		case 21:
			postCase20(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSfx(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSfx(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			break;
		case 4:
		case 5:
			postCase3(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSfx(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			break;
		case 6:
			postCase5(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			if(!smlayer_isSoundRunning(88))
				smlayer_startSfx(88);
			smlayer_soundSetPan(88, ((_actor[0].x+160)>>2)+64);
			break;
		case 7:
		case 8:
			postCase6(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 9:
		case 23:
			postCase8(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 10:
			postCase9(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 11:
		case 20:
		case 22:
			postCase10(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 13:
			postCase12(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			needMore = true;
			if(!smlayer_isSoundRunning(89)) {
				smlayer_startSfx(89);
				smlayer_soundSetPriority(89, 100);
			}
			tmpSnd = _enemy[_currEnemy].sound;
			if(!smlayer_isSoundRunning(tmpSnd)) {
				smlayer_startSfx(tmpSnd);
				smlayer_soundSetPriority(tmpSnd, 100);
			}
			smlayer_soundSetPan(89, ((_actor[0].x+160)>>2)+64);
			smlayer_soundSetPan(tmpSnd, ((_actor[1].x+160)>>2)+64);
			break;
		case 24:
			if(!smlayer_isSoundRunning(90)) {
				smlayer_startSfx(90);
				smlayer_soundSetPriority(90, 100);
			}
			postCase23(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 15:
		case 16:
			postCase14(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
			break;
		case 25:
		case 26:
			break;
		}

		if (_currScenePropIdx)
			postCaseAll(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
	
		_actor[0].frame++;
		_actor[0].act[3].frame++;
		_actor[0].act[2].frame++;
		_actor[0].act[1].frame++;
		_actor[0].act[0].frame++;
		_actor[1].act[3].frame++;
		_actor[1].frame++;
		_actor[1].act[2].frame++;
		_actor[1].act[1].frame++;
		_actor[1].act[0].frame++;
	}
	
	if (!_val115w) {
		smlayer_overrideDrawActorAt(&renderBitmap[0], renderBitmap[2], renderBitmap[3]);
		_isBenCut = 0;
	}
	
	if (_isBenCut)
		smlayer_drawSomething(renderBitmap, codecparam, 89, 56, 1, _smush_bencutNut, 0, 0, 0);
	
	if (!_keyboardDisable && !_val116w)
		_vm->processActors();
	
	if (needMore)
		postCaseMore(renderBitmap, codecparam, setupsan12, setupsan13, curFrame, maxFrame);
	
	_lastKey = 0;
	_tiresRustle = false;
}

void Insane::postCase11(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		if (_firstBattle) {
			smush_setToFinish();
		} else {
			queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0, 
							 _continueFrame, 1300);
		}
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase0(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	turnBen(true);
	
	if (!curFrame || curFrame == 420)
		smlayer_setFluPalette(_smush_roadrashRip, 0);
	
	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);
	
	_val121_ = false;
	_val119_ = false;
	_val120_ = false;
	_val122_ = false;
	_val123_ = false;
	_continueFrame1 = curFrame;
}

void Insane::postCase17(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		if (_currSceneId == 18) {
			queueSceneSwitch(17, _smush_minedrivFlu, "minedriv.san", 64, 0, 
							 _continueFrame1, 1300);
			setWordInString(_numberArray, 9, 1);
		} else {
			queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
							 _continueFrame1, 1300);
			setWordInString(_numberArray, 9, 0);
		}
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase16(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	char buf[12];
	int32 tmp;
	
	turnBen(true);
	sprintf(buf, "^f01%02o", curFrame & 0x3f);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 180, 168, 1, 2, 0, "%s", buf);
	tmp = 400-curFrame;
	
	if (tmp < 0)
		tmp += 1300;
	
	sprintf(buf, "^f01%04d", tmp);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 202, 168, 1, 2, 0, "%s", buf);
	
	sprintf(buf, "^f01%02o", curFrame & 0xff);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 140, 168, 1, 2, 0, "%s", buf);
	smlayer_showStatusMsg(-1, renderBitmap, codecparam, 170, 43, 1, 2, 0, "%s", buf);
	
	smlayer_drawSomething(renderBitmap, codecparam, 0, 0, 1, _smush_bensgoggNut, 0, 0, 0);
	
	if (!_val124_)
		smlayer_drawSomething(renderBitmap, codecparam, 24, 170, 1, 
							  _smush_iconsNut, 23, 0, 0);
	
	if (!curFrame)
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
	
	if (curFrame >= maxFrame) {
		smush_rewindCurrentSan(1088, -1, -1);
		smlayer_setFluPalette(_smush_goglpaltRip, 0);
	}
	_val121_ = false;
	_val123_ = false;
	_val119_ = false;
	_val120_ = false;
	_val124_ = false;
	_counter1++;
	_continueFrame1 = curFrame;
	if (_counter1 >= 10)
		_counter1 = 0;
}

void Insane::postCase1(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct fluConf *flu;

	if ((curFrame >= maxFrame) && !_needSceneSwitch) {
		flu = &_fluConf[14 + _iactSceneId2];
		queueSceneSwitch(flu->sceneId, *flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase2(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	turnBen(_battleScene != 0);
	turnEnemy(true);
	
	if (!curFrame)
		smlayer_setFluPalette(_smush_roadrashRip, 0);

	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);

	_val121_ = false;
	_val119_ = false;
	_val120_ = false;
	_continueFrame = curFrame;
}

void Insane::postCase20(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	turnBen(true);
	turnEnemy(true);
	
	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);
	
	_val121_ = false;
	_val119_ = false;
	_val120_ = false;
	_continueFrame = curFrame;
}

void Insane::postCase3(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	turnBen(true);
	
	if (_actor[0].x >= 158 && _actor[0].x <= 168) {
		if (!smlayer_isSoundRunning(86))
			smlayer_startSfx(86);
	} else {
		if (!smlayer_isSoundRunning(86))
			smlayer_stopSound(86);
	}

	if (curFrame >= maxFrame) {
		if (_currSceneId == 4) {
			if (!_needSceneSwitch) {
				if (readArray(_numberArray, 6)) {
					if (readArray(_numberArray, 4))
						queueSceneSwitch(14, 0, "hitdust2.san", 64, 0, 0, 0);
					else
						queueSceneSwitch(14, 0, "hitdust4.san", 64, 0, 0, 0);
				} else {
					if (readArray(_numberArray, 4))
						queueSceneSwitch(14, 0, "hitdust1.san", 64, 0, 0, 0);
					else
						queueSceneSwitch(14, 0, "hitdust3.san", 64, 0, 0, 0);
				}
			}
		} else {
			if (readArray(_numberArray, 4)) {
				if (!_needSceneSwitch)
					queueSceneSwitch(15, 0, "vistthru.san", 64, 0, 0, 0);
			} else {
				setWordInString(_numberArray, 1, _val53d);
				smush_setToFinish();
			}
		}
	}

	_val212_ = false;
	_val120_ = false;
	_val119_ = false;
	_iactSceneId = 0;
}

void Insane::postCase5(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	turnBen(true);

	if (_actor[0].x >= 158 && _actor[0].x <= 168) {
		if (!smlayer_isSoundRunning(86))
			smlayer_startSfx(86);
	} else {
		if (!smlayer_isSoundRunning(86))
			smlayer_stopSound(86);
	}

	if (curFrame >= maxFrame) {
		if (readArray(_numberArray, 4)) {
			if (!_needSceneSwitch)
				queueSceneSwitch(15, 0, "chasthru.san", 64, 0, 0, 0);
		} else {
			if (readArray(_numberArray, 5)) {
				setWordInString(_numberArray, 1, _val57d);
				smush_setToFinish();
			} else {
				queueSceneSwitch(15, 0, "chasout.san", 64, 0, 0, 0);
			}
		}
	}
	
	_val212_ = false;
	_val120_ = false;
	_val119_ = false;
	_iactSceneId = 0;
}

void Insane::postCase6(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct fluConf *flu;

	if ((curFrame >= maxFrame) && !_needSceneSwitch) {
		if (_currSceneId == 8)
			flu = &_fluConf[7 + _iactSceneId2];
		else
			flu = &_fluConf[0 + _iactSceneId2];

		queueSceneSwitch(flu->sceneId, *flu->fluPtr, flu->filenamePtr, 64, 0, 
						 flu->startFrame, flu->numFrames);
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase8(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		_actor[0].damage = 0;

		if (_firstBattle) {
			queueSceneSwitch(13, _smush_minefiteFlu, "minefite.san", 64, 0,
							 _continueFrame, 1300);
		} else {
			if (_currSceneId == 23) {
				queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
			} else {
				queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
							 _continueFrame, 1300);
			}
		}
 	}
	
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase9(byte *renderBitmap, int32 codecparam, int32 setupsan12,
					   int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		_actor[0].damage = 0;
		queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
						 _continueFrame1, 1300);
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase10(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame && !_needSceneSwitch) {
		_actor[0].damage = 0;

		switch (_currSceneId) {
		case 20:
			setWordInString(_numberArray, 8, 1);
			queueSceneSwitch(12, 0, "liftgog.san", 0, 0, 0, 0);
			break;
		case 22:
			setWordInString(_numberArray, 1, _val54d);
			smush_setToFinish();
			break;
		default:
			if (_actor[0].inventory[_enemy[_currEnemy].weapon]) {
				queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
								 _continueFrame, 1300);
				break;
			}

			switch (_enemy[_currEnemy].weapon) {
			case INV_CHAIN:
				_actor[1].inventory[INV_CHAIN] = 1;
				queueSceneSwitch(12, 0, "liftchay.san", 0, 0, 0, 0);
				break;
			case INV_CHAINSAW:
				_actor[1].inventory[INV_CHAINSAW] = 1;
				queueSceneSwitch(12, 0, "liftsaw.san", 0, 0, 0, 0);
				break;
			case INV_MACE:
				_actor[1].inventory[INV_MACE] = 1;
				queueSceneSwitch(12, 0, "liftmace.san", 0, 0, 0, 0);
				break;
			case INV_2X4:
				_actor[1].inventory[INV_2X4] = 1;
				queueSceneSwitch(12, 0, "liftbord.san", 0, 0, 0, 0);
				break;
			default:
				queueSceneSwitch(1, _smush_minedrivFlu, "minedriv.san", 64, 0,
								 _continueFrame, 1300);
				break;
			}
		}
 	}
	
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase12(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (_actor[1].y <= 200) {
		initScene(3);
		_actor[1].y = 200;

		switch (_currEnemy) {
		case EN_ROTT2:
			turnBen(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(32, 0, 1);
			else
				prepareScenePropScene(33, 0, 1);
			break;
		case EN_ROTT3:
			turnBen(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(25, 0, 1);
			break;
		case EN_VULTF1:
			turnBen(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(2, 0, 1);
			break;
		case EN_VULTF2:
			turnBen(true);

			if (_enemy[1].field_8 <= 1)
				prepareScenePropScene(9, 0, 1);
			else
				prepareScenePropScene(16, 0, 1);
			break;
		case EN_VULTM2:
			turnBen(true);

			prepareScenePropScene(18, 0, 1);
			_battleScene = false;
			break;
		case EN_TORQUE:
			turnBen(false);
			setWordInString(_numberArray, 1, _val51d);
			smush_setToFinish();
			break;
		case EN_ROTT1:
		case EN_VULTM1:
		case EN_CAVEFISH:
		default:
			turnBen(true);
			break;
		}
	} else {
		switch (_currEnemy) {
		case EN_VULTM2:
			if (_enemy[EN_VULTM2].field_8 <= 1)
				turnBen(false);
			else
				turnBen(true);
			break;
		case EN_TORQUE:
			turnBen(false);
			if (_actor[1].y != 300)
				prepareScenePropScene(57, 1, 0);
			break;
		default:
			turnBen(true);
		}
		_actor[1].y -= (_actor[1].y - 200) / 20 + 1;
	}

	turnEnemy(false);

	if (curFrame == 0)
		smlayer_setFluPalette(_smush_roadrashRip, 0);

	if (curFrame >= maxFrame)
		smush_rewindCurrentSan(1088, -1, -1);

	_val119_ = 0;
	_val120_ = 0;
	_continueFrame = curFrame;
}

void Insane::postCase23(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame) {
		if (_currSceneId == 24)
			queueSceneSwitch(21, 0, "rottfite.san", 64, 0, 0, 0);
	
		if (readArray(_numberArray, 6) && readArray(_numberArray, 4))
			queueSceneSwitch(16, 0, "limocrsh.san", 64, 0, 0, 0);
	
		queueSceneSwitch(5, 0, "tovista2.san", 64, 0, 0, 290);
	}
	_val119_ = false;
	_val120_ = false;
}

void Insane::postCase14(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (curFrame >= maxFrame) {
		if (_currSceneId == 16) {
			setWordInString(_numberArray, 4, 0);
			setWordInString(_numberArray, 5, 1);
			setWordInString(_numberArray, 1, _val56d);
			setWordInString(_numberArray, 3, _val55d);
			smush_setToFinish();
		} else {
			switch (_tempSceneId) {
			case 5:
				queueSceneSwitch(6, 0, "toranch.san", 64, 0, 0, 530);
				break;
			case 6:
				queueSceneSwitch(4, 0, "tovista1.san", 64, 0, 0, 230);
				break;
			}
		}
	}

	_val119_ = false;
	_val120_ = false;
}

void Insane::postCaseAll(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						 int32 setupsan13, int32 curFrame, int32 maxFrame) {
	struct sceneProp *tsceneProp;

	tsceneProp = &_sceneProp[_currScenePropIdx + _currScenePropSubIdx];
	if (tsceneProp->actor != -1) {
		if (_actor[tsceneProp->actor].field_54) {
			tsceneProp->counter++;
			if (!_actor[tsceneProp->actor].runningSound || ConfMan.getBool("subtitles")) {
				if (_actor[tsceneProp->actor].act[3].state == 72 &&
					_currTrsMsg) {
					smush_setPaletteValue(1, tsceneProp->r, tsceneProp->g, tsceneProp->b);
					smush_setPaletteValue(2, 0, 0, 0);
					smlayer_showStatusMsg(-1, renderBitmap, codecparam, 160, 20, 1, 2, 5,
										  "^f00%s", _currTrsMsg);
				}
			}
		} else {
			_currScenePropSubIdx = tsceneProp->index;
			if (_currScenePropSubIdx && _currScenePropIdx) {
				tsceneProp = &_sceneProp[_currScenePropIdx + _currScenePropSubIdx];
				tsceneProp->counter = 0;
				if (tsceneProp->trsId)
					_currTrsMsg = handleTrsTag(_trsFilePtr, tsceneProp->trsId);
				else
					_currTrsMsg = 0;

				if (tsceneProp->actor != -1) {
					_actor[tsceneProp->actor].field_54 = 1;
					_actor[tsceneProp->actor].act[3].state = 117;
					_actor[tsceneProp->actor].scenePropSubIdx = _currScenePropSubIdx;
				}
			} else {
				_currScenePropIdx = 0;
				_currTrsMsg = 0;
				_currScenePropSubIdx = 0;
				_actor[0].defunct = 0;
				_actor[1].defunct = 0;
				_battleScene = true;
			}
		}
	}
	_val119_ = 0;
	_val120_ = 0;
	_continueFrame = curFrame;
}

void Insane::postCaseMore(byte *renderBitmap, int32 codecparam, int32 setupsan12,
						  int32 setupsan13, int32 curFrame, int32 maxFrame) {
	if (_actor[0].weapon <= 7) {
		smlayer_drawSomething(renderBitmap, codecparam, 5, 160, 1, _smush_iconsNut,
							  _actor[0].weapon + 11, 0, 0);
	}
}

}
