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

#include "common/scummsys.h"
#include "common/algorithm.h"
#include "xeen/saves.h"

namespace Xeen {

AttributePair::AttributePair() {
	_temporary = _permanent = 0;
}

void AttributePair::synchronize(Common::Serializer &s) {
	s.syncAsByte(_permanent);
	s.syncAsByte(_temporary);
}

/*------------------------------------------------------------------------*/

Roster::Roster() {
	_partyCount = 0;
	_realPartyCount = 0;
	Common::fill(&_partyMembers[0], &_partyMembers[8], 0);
	_mazeDirection = DIR_NORTH;
	_mazeId = _priorMazeId = 0;
	_levitateActive = false;
	_automapOn = false;
	_wizardEyeActive = false;
	_clairvoyanceActive = false;
	_walkOnWaterActive = false;
	_blessedActive = false;
	_powerShieldActive = false;
	_holyBonusActive = false;
	_heroismActive = false;
	_difficulty = ADVENTURER;
	_cloudsEnd = false;
	_darkSideEnd = false;
	_worldEnd = false;
	hour_maybe = 0;
	_day = 0;
	_year = 0;
	_minutes = 0;
	_food = 0;
	_lightCount = 0;
	_torchCount = 0;
	_fireResistence = 0;
	_electricityResistence = 0;
	_coldResistence = 0;
	_poisonResistence = 0;
	_deathCount = 0;
	_winCount = 0;
	_lossCount = 0;
	_gold = 0;
	_gems = 0;
	_bankGold = 0;
	_bankGems = 0;
	_totalTime = 0;
	_rested = false;
	Common::fill(&_gameFlags[0], &_gameFlags[256], false);
	Common::fill(&_autoNotes[0], &_autoNotes[128], false);
	Common::fill(&_quests[0], &_quests[64], false);
	Common::fill(&_questItems[0], &_questItems[65], 0);
	Common::fill(&_characterFlags[0][0], &_characterFlags[30][24], false);
}

void Roster::synchronize(Common::Serializer &s) {
	byte dummy[30];
	Common::fill(&dummy[0], &dummy[30], 0);

	s.syncAsByte(_partyCount);
	s.syncAsByte(_realPartyCount);
	for (int i = 0; i < 8; ++i)
		s.syncAsByte(_partyMembers[i]);
	s.syncAsByte(_mazeDirection);
	s.syncAsByte(_mazePosition.x);
	s.syncAsByte(_mazePosition.y);
	s.syncAsByte(_mazeId);
	
	// Game configuration flags not used in this implementation
	s.syncBytes(dummy, 3);

	s.syncAsByte(_priorMazeId);
	s.syncAsByte(_levitateActive);
	s.syncAsByte(_automapOn);
	s.syncAsByte(_wizardEyeActive);
	s.syncAsByte(_clairvoyanceActive);
	s.syncAsByte(_walkOnWaterActive);
	s.syncAsByte(_blessedActive);
	s.syncAsByte(_powerShieldActive);
	s.syncAsByte(_holyBonusActive);
	s.syncAsByte(_heroismActive);
	s.syncAsByte(_difficulty);

	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithWeapons[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithArmor[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithAccessories[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithMisc[i].synchronize(s);

	s.syncAsUint16LE(_cloudsEnd);
	s.syncAsUint16LE(_darkSideEnd);
	s.syncAsUint16LE(_worldEnd);
	s.syncAsUint16LE(hour_maybe);
	s.syncAsUint16LE(_day);
	s.syncAsUint16LE(_year);
	s.syncAsUint16LE(_minutes);
	s.syncAsUint16LE(_food);
	s.syncAsUint16LE(_lightCount);
	s.syncAsUint16LE(_torchCount);
	s.syncAsUint16LE(_fireResistence);
	s.syncAsUint16LE(_electricityResistence);
	s.syncAsUint16LE(_coldResistence);
	s.syncAsUint16LE(_poisonResistence);
	s.syncAsUint16LE(_deathCount);
	s.syncAsUint16LE(_winCount);
	s.syncAsUint16LE(_lossCount);
	s.syncAsUint32LE(_gold);
	s.syncAsUint32LE(_gems);
	s.syncAsUint32LE(_bankGold);
	s.syncAsUint32LE(_bankGems);
	s.syncAsUint32LE(_totalTime);
	s.syncAsByte(_rested);
	SavesManager::syncBitFlags(s, &_gameFlags[0], &_gameFlags[512]);
	SavesManager::syncBitFlags(s, &_autoNotes[0], &_autoNotes[128]);
	SavesManager::syncBitFlags(s, &_quests[0], &_quests[64]);
	
	for (int i = 0; i < 85; ++i)
		s.syncAsByte(_questItems[i]);

	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithWeapons2[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithArmor2[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithAccessories2[i].synchronize(s);
	for (int i = 0; ITEMS_COUNT; ++i)
		_blacksmithMisc2[i].synchronize(s);
	
	SavesManager::syncBitFlags(s, &_characterFlags[0][0], &_characterFlags[30][24]);
	s.syncBytes(&dummy[0], 30);
}

/*------------------------------------------------------------------------*/

PlayerStruct::PlayerStruct() {
	_sex = MALE;
	_race = HUMAN;
	_xeenSide = 0;
	_class = KNIGHT;
	_ACTemp = 0;
	_dbDay = 0;
	_tempAge = 0;
	Common::fill(&_skills[0], &_skills[18], 0);
	Common::fill(&_awards[0], &_awards[64], false);
	Common::fill(&_spells[9], &_spells[40], false);
	_lloydMap = 0;
	_hasSpells = false;
	_currentSpell = 0;
	_quickOption = 0;
	_lloydSide = 0;
	Common::fill(&_conditions[0], &_conditions[16], 0);
	_townUnknown = 0;
	_unknown2 = 0;
	_currentHp = 0;
	_currentSp = 0;
	_ybDay = 0;
	_experience = 0;
	_currentAdventuringSpell = 0;
	_currentCombatSpell = 0;
}

void PlayerStruct::synchronize(Common::Serializer &s) {
	char name[16];
	Common::fill(&name[0], &name[16], '\0');
	strncpy(name, _name.c_str(), 16);
	s.syncBytes((byte *)name, 16);

	if (s.isLoading())
		_name = Common::String(name);

	s.syncAsByte(_sex);
	s.syncAsByte(_race);
	s.syncAsByte(_xeenSide);
	s.syncAsByte(_class);

	_might.synchronize(s);
	_intellect.synchronize(s);
	_personality.synchronize(s);
	_endurance.synchronize(s);
	_speed.synchronize(s);
	_accuracy.synchronize(s);
	_luck.synchronize(s);
	s.syncAsByte(_ACTemp);
	_level.synchronize(s);
	s.syncAsByte(_dbDay);
	s.syncAsByte(_tempAge);
	
	for (int i = 0; i < 18; ++i)
		s.syncAsByte(_skills[i]);
	SavesManager::syncBitFlags(s, &_awards[0], &_awards[64]);
	SavesManager::syncBitFlags(s, &_spells[0], &_spells[40]);
	
	s.syncAsByte(_lloydMap);
	s.syncAsByte(_lloydPosition.x);
	s.syncAsByte(_lloydPosition.y);
	s.syncAsByte(_hasSpells);
	s.syncAsByte(_currentSpell);
	s.syncAsByte(_quickOption);

	for (int i = 0; i < 9; ++i)
		_weapons[i].synchronize(s);
	for (int i = 0; i < 9; ++i)
		_armor[i].synchronize(s);
	for (int i = 0; i < 9; ++i)
		_accessories[i].synchronize(s);
	for (int i = 0; i < 9; ++i)
		_misc[i].synchronize(s);

	s.syncAsByte(_lloydSide);
	_fireResistence.synchronize(s);
	_coldResistence.synchronize(s);
	_electricityResistence.synchronize(s);
	_poisonResistence.synchronize(s);
	_energyResistence.synchronize(s);
	_magicResistence.synchronize(s);
	
	for (int i = 0; i < 16; ++i)
		s.syncAsByte(_conditions[i]);

	s.syncAsUint16LE(_townUnknown);
	s.syncAsByte(_unknown2);
	s.syncAsUint16LE(_currentHp);
	s.syncAsUint16LE(_currentSp);
	s.syncAsUint16LE(_ybDay);
	s.syncAsUint32LE(_experience);
	s.syncAsByte(_currentAdventuringSpell);
	s.syncAsByte(_currentCombatSpell);
}

/*------------------------------------------------------------------------*/

/**
 * Synchronizes a boolean array as a bitfield set
 */
void SavesManager::syncBitFlags(Common::Serializer &s, bool *startP, bool *endP) {
	byte data = 0;

	int bitCounter = 0;
	for (bool *p = startP; p <= endP; ++p, ++bitCounter) {
		if (bitCounter != 0 && (bitCounter % 8) == 0) {
			s.syncAsByte(data);
			if (p == endP)
				break;

			if (s.isSaving())
				data = 0;
		}

		if (s.isLoading())
			*p = (data >> bitCounter) != 0;
		else if (*p)
			data |= 1 << bitCounter;
	}
}

/*------------------------------------------------------------------------*/


} // End of namespace Xeen
