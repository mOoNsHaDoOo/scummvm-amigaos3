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
/*
 This is the list of the built in functions

 true or false states if it's a used function
 in the current version of the engine,
 but that value currently isn't used anywhere
 */
FUNC(true, say)
FUNC(true, skipSpeech)
FUNC(true, statusText)
FUNC(true, pause)
FUNC(true, onLeftMouse)
FUNC(true, onRightMouse)
FUNC(true, setCursor)
FUNC(true, addOverlay)
FUNC(true, addCharacter)
FUNC(true, playSound)
FUNC(true, getMouseX)
FUNC(true, getMouseY)
FUNC(true, addScreenRegion)
FUNC(true, onMoveMouse)
FUNC(true, onFocusChange)
FUNC(true, getOverObject)
FUNC(true, blankScreen)
FUNC(true, moveCharacter)
FUNC(true, onKeyboard)
FUNC(true, getObjectX)
FUNC(true, getObjectY)
FUNC(true, random)
FUNC(true, spawnSub)
FUNC(true, blankArea)
FUNC(true, hideCharacter)
FUNC(true, showCharacter)
FUNC(true, callEvent)
FUNC(true, removeScreenRegion)
FUNC(true, animate)
FUNC(true, turnCharacter)
FUNC(true, removeAllCharacters)
FUNC(true, removeAllScreenRegions)
FUNC(true, setScale)
FUNC(true, newStack)
FUNC(true, pushToStack)
FUNC(true, popFromStack)
FUNC(true, clearStatus)
FUNC(true, addStatus)
FUNC(true, removeLastStatus)
FUNC(true, lightStatus)
FUNC(true, getStatusText)
FUNC(true, setStatusColour)
FUNC(true, deleteFromStack)
FUNC(true, freeze)
FUNC(true, unfreeze)
FUNC(true, pasteImage)
FUNC(true, copyStack)
FUNC(true, completeTimers)
FUNC(true, setCharacterDrawMode)
FUNC(true, anim)
FUNC(true, costume)
FUNC(true, pickOne)
FUNC(true, setCostume)
FUNC(true, wait)
FUNC(true, somethingSpeaking)
FUNC(true, substring)
FUNC(true, stringLength)
FUNC(true, darkBackground)
FUNC(true, saveGame)
FUNC(true, loadGame)
FUNC(true, quitGame)
FUNC(true, rename)
FUNC(true, stackSize)
FUNC(true, pasteString)
FUNC(true, startMusic)
FUNC(true, setDefaultMusicVolume)
FUNC(true, setMusicVolume)
FUNC(true, stopMusic)
FUNC(true, stopSound)
FUNC(true, setFont)
FUNC(true, alignStatus)
FUNC(true, showFloor)
FUNC(true, showBoxes)
FUNC(true, positionStatus)
FUNC(true, setFloor)
FUNC(true, forceCharacter)
FUNC(true, jumpCharacter)
FUNC(true, peekStart)
FUNC(true, peekEnd)
FUNC(true, enqueue)
FUNC(true, setZBuffer)
FUNC(true, getMatchingFiles)
FUNC(true, inFont)
FUNC(true, onLeftMouseUp)
FUNC(true, onRightMouseUp)
FUNC(true, loopSound)
FUNC(true, removeCharacter)
FUNC(true, stopCharacter)
FUNC(true, launch)
FUNC(true, howFrozen)
FUNC(true, setPasteColour)
FUNC(true, setLitStatusColour)
FUNC(true, fileExists)
FUNC(true, floatCharacter)
FUNC(true, cancelSub)
FUNC(true, setCharacterWalkSpeed)
FUNC(true, deleteAllFromStack)
FUNC(true, setCharacterExtra)
FUNC(true, mixOverlay)
FUNC(true, pasteCharacter)
FUNC(true, setSceneDimensions)
FUNC(true, aimCamera)
FUNC(true, getMouseScreenX)
FUNC(true, getMouseScreenY)
FUNC(true, setDefaultSoundVolume)
FUNC(true, setSoundVolume)
FUNC(true, setSoundLoopPoints)
FUNC(true, setSpeechMode)
FUNC(true, setLightMap)
FUNC(true, think)
FUNC(true, getCharacterDirection)
FUNC(true, isCharacter)
FUNC(true, isScreenRegion)
FUNC(true, isMoving)
FUNC(true, deleteFile)
FUNC(true, renameFile)
FUNC(true, hardScroll)
FUNC(true, stringWidth)
FUNC(true, setSpeechSpeed)
FUNC(true, normalCharacter)
FUNC(true, fetchEvent)
FUNC(true, transitionLevel)
FUNC(true, spinCharacter)
FUNC(true, setFontSpacing)
FUNC(true, burnString)
FUNC(true, captureAllKeys)
FUNC(true, cacheSound)
FUNC(true, setCharacterSpinSpeed)
FUNC(true, transitionMode)
FUNC(false, _rem_movieStart)
FUNC(false, _rem_movieAbort)
FUNC(false, _rem_moviePlaying)
FUNC(false, _rem_updateDisplay)
FUNC(true, getSoundCache)
FUNC(true, saveCustomData)
FUNC(true, loadCustomData)
FUNC(true, setCustomEncoding)
FUNC(true, freeSound)
FUNC(true, parallaxAdd)
FUNC(true, parallaxClear)
FUNC(true, setBlankColour)
FUNC(true, setBurnColour)
FUNC(true, getPixelColour)
FUNC(true, makeFastArray)
FUNC(true, getCharacterScale)
FUNC(true, getLanguageID)
FUNC(false, _rem_launchWith)
FUNC(true, getFramesPerSecond)
FUNC(true, showThumbnail)
FUNC(true, setThumbnailSize)
FUNC(true, hasFlag)
FUNC(true, snapshotGrab)
FUNC(true, snapshotClear)
FUNC(true, bodgeFilenames)
FUNC(false, _rem_registryGetString)
FUNC(true, quitWithFatalError)
FUNC(true, _rem_setCharacterAA)
FUNC(true, _rem_setMaximumAA)
FUNC(true, setBackgroundEffect)
FUNC(true, doBackgroundEffect)
FUNC(true, setCharacterAngleOffset)
FUNC(true, setCharacterTransparency)
FUNC(true, setCharacterColourise)
FUNC(true, zoomCamera)
FUNC(true, playMovie)
FUNC(true, stopMovie)
FUNC(true, pauseMovie)
