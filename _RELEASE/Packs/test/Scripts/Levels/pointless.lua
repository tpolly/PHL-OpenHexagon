-- include useful files
u_execScript("utils.lua")
u_execScript("common.lua")
u_execScript("commonpatterns.lua")

-- this function adds a pattern to the timeline based on a key
function addPattern(mKey)
		if mKey == 0 then pAltBarrage(math.random(5, 10), 3) 
	elseif mKey == 1 then pRandomBarrage(math.random(5,10), 4)
	elseif mKey == 2 then pBarrageSpiral(math.random(5, 10), 1, 1)
	elseif mKey == 3 then pInverseBarrage(math.random(3,5))
	elseif mKey == 4 then pTunnel(math.random(2, 6))
	elseif mKey == 5 then pMirrorWallStrip(math.random(3, 10), 1)
	elseif mKey == 6 then pWallExVortex(math.random(3,5), 1, 0.1)
	elseif mKey == 7 then pWallRandom(math.random(20,50), 2)
	end
end

-- shuffle the keys, and then call them to add all the patterns
-- shuffling is better than randomizing - it guarantees all the patterns will be called
keys = { 0,1,2,3,4,5,6,7 }
keys = shuffle(keys)
index = 0

-- onInit is an hardcoded function that is called when the level is first loaded
function onInit()
	l_setSpeedMult(1.75)
	l_setSpeedInc(0)
	l_setRotationSpeed(0.10)
	l_setRotationSpeedMax(0.2)
	l_setRotationSpeedInc(0)
	l_setDelayMult(1)
	l_setDelayInc(0)
	l_setFastSpin(0.0)
	l_setSides(6)
	l_setSidesMin(4)
	l_setSidesMax(9)
	l_setIncTime(5)
	l_setMaxInc(100)

	l_setPulseMin(75)
	l_setPulseMax(91)
	l_setPulseSpeed(1.2)
	l_setPulseSpeedR(1)
	l_setPulseDelayMax(23.9)

	l_setBeatPulseMax(1)
	l_setBeatPulseDelayMax(1)

	--enableSwapIfDMGreaterThan(2.5)
	--disableIncIfDMGreaterThan(3)
end

-- onLoad is an hardcoded function that is called when the level is started/restarted
function onLoad()
end

-- onStep is an hardcoded function that is called when the level timeline is empty
-- onStep should contain your pattern spawning logic
function onStep()	
	addPattern(keys[index])
	index = index + 1
	
	if index - 1 == #keys then
		index = 0
	end
end

-- onIncrement is an hardcoded function that is called when the level difficulty is incremented
function onIncrement()
end

-- onUnload is an hardcoded function that is called when the level is closed/restarted
function onUnload()
end

-- onUpdate is an hardcoded function that is called every frame
function onUpdate(mFrameTime)
end
