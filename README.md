<img src="http://anooserve.com:2288/job/BoopAI/badge/icon"/>
# BoopAI
##A neural network with genetic algorithms experiment
Little creatures that evolve using a Neural Network "brain". The plan is for a few "tournaments" to run simultaneously and report back to a master "world" controller which will handle the selective breeding of boops to increase their inteligence.

Currently being trained to eat as much food as they can, the code is in a non-functioning state while I add async calls.

###ToDo:
- Fix async code. I fear there are a few pointers being left behind during a call which, later, are being dereferenced.
- Apply sensor logic. Check for: food, other boops, and walls. Eat food, hunt boops and avoid walls.
  - Add more walls? Obsticles?
- Make walls hurt. This will help natural selection for boops that avoid walls.
- Neuron View. Graphics code to let us see what a selected boop is thinking.
  - Which boop is selected should be choosable, preferably with the mouse.
- Pause, menu and other buttons on the keyboard.
  - Pause would be needed to select a boop for neuron view.

###October: Getting smarterer!
![Generation Graph](http://puu.sh/jZH5o/8083d24729.png)
