# CS330 Programming Assignment 2 Chase the rabbit
# Email: erb0023@uah.edu

import math
import numpy as np

# Define constants for different steering behaviors
CONTINUE = 1
SEEK = 6
FLEE = 7
ARRIVE = 8
FOLLOW_PATH = 11

# Initialize simulation parameters
time = 0
deltaTime = 0.5  # Duration of time step
stopTime = 125  # Time of last time step

# Define a function to calculate the length of a vector
def length(vector):
    return np.linalg.norm(vector)

# Define a function to normalize a vector
def normalize(vector):
    vLength = length(vector)
    if vLength == 0:
        return vector
    return vector / vLength
    
# Define a function to calculate the dot product of two vectors
def vectorDot(A, B):
    return sum(A * B)
    
# Define a function to find the closest point on a line segment to a given point
def closestPointSegment(Q, A, B):
    T = vectorDot((Q-A), (B-A)) / vectorDot((B-A), (B-A))
    if T <= 0:
        return A
    elif T >= 1:
        return B
    else:
        return A+(T * (B-A))

# Define a function to calculate the distance between two points
def distancePointPoint(A, B):
    return (math.sqrt((B[0] - A[0])**2 + (B[1] - A[1])**2))

class Path:
    
    # Define a method to assemble a path from a list of points
    def assemble(pathID, pathX, pathZ):
        segments = len(pathX) - 1
        distance = np.zeros(segments + 1)
        
        for i in range(1, segments+1):
            distance[i] = distance[i - 1] + distancePointPoint([pathX[i - 1], pathZ[i - 1]], [pathX[i], pathZ[i]])
        
        pathParam = np.zeros(segments + 1)
        maxDistance = max(distance)
        
        if maxDistance > 0:
            pathParam = distance / maxDistance
            
        return {
            'id': pathID,
            'x': pathX,
            'y': pathZ,
            'distance': distance.tolist(),
            'param': pathParam.tolist(),
            'segments': segments
        }
    
    # Define a method to get the position on a path at a given parameter value
    def getPosition(path, param):
        i = np.max(np.where(param > path['param'])[0])  # Find the largest index where param is greater
        A = np.array([path['x'][i], path['y'][i]])
        B = np.array([path['x'][i + 1], path['y'][i + 1]])
        
        T = (param - path['param'][i]) / (path['param'][i + 1] - path['param'][i])
        P = A + (T * (B - A))
        
        return P
    
    # Define a method to get the parameter value of a point on a path
    def getParam(path, position):
        closestDistance = np.inf
        closestSegment = 0
        closestPoint = None
        
        for i in range(path['segments']):
            A = np.array([path['x'][i], path['y'][i]])
            B = np.array([path['x'][i + 1], path['y'][i + 1]])

            checkPoint = closestPointSegment(np.array(position), A, B)
            checkDistance = distancePointPoint(np.array(position), checkPoint)
            
            if checkDistance < closestDistance:
                closestPoint = checkPoint
                closestDistance = checkDistance
                closestSegment = i
        
        # Compute path parameter of the closest point
        A = np.array([path['x'][closestSegment], path['y'][closestSegment]])
        A_param = path['param'][closestSegment]
        B = np.array([path['x'][closestSegment + 1], path['y'][closestSegment + 1]])
        B_param = path['param'][closestSegment + 1]
        C = closestPoint
        
        T = length(C - A) / length(B - A)
        C_param = A_param + (T * (B_param - A_param))
        
        return C_param

# Define a class to represent a steering output
class SteeringOutput(object):
    def __init__(self):
        self.linear = np.array([0.0, 0.0])
        self.angular = 0.0

# Define a class to represent a character
class Character:
    def __init__(self):
        self.ID = 0  
        self.steer = 2  
        self.position = np.array([0.0, 0.0])  
        self.velocity = np.array([0.0, 0.0])  
        self.linear = np.array([0.0, 0.0])
        self.orientation = 0.0  
        self.rotation = 0.0
        self.angular = 0.0
        self.maxVelocity = 0.0  
        self.maxLinear = 0.0
        self.maxRotation = 0.0  
        self.maxAngular = 0.0
        self.target = None  
        self.arriveRadius = 0.0  
        self.arriveSlow = 0.0  
        self.arriveTime = 0.0  
        self.colCollided = False
    
    # Define a method to update the character's state
    def update(self, steering, time):
        self.position = np.add(self.position, self.velocity * time)
        self.orientation += self.rotation * time

        self.velocity = np.add(self.velocity, steering.linear * time)
        self.rotation += steering.angular * time

        if length(self.velocity) > self.maxVelocity:
            self.velocity = normalize(self.velocity) * self.maxVelocity

        self.linear = steering.linear
        self.angular = steering.angular

    # Define a method to get the steering output for the continue behavior
    def getSteeringContinue(self):
        result = SteeringOutput()
        result.linear = self.linear
        result.angular = self.angular
        return result
    
    # Define a method to get the steering output for the seek behavior
    def getSteeringSeek(self, target):
        result = SteeringOutput()
        result.linear = target.position - self.position
        result.linear = normalize(result.linear) * self.maxLinear
        result.angular = 0.0
        return result
    
    # Define a method to get the steering output for the flee behavior
    def getSteeringFlee(self, target):
        result = SteeringOutput()
        result.linear = self.position - target.position
        result.linear = normalize(result.linear) * self.maxLinear
        result.angular = 0.0
        return result
    
    # Define a method to get the steering output for the arrive behavior
    def getSteeringArrive(self, target):
        result = SteeringOutput()
        direction = target.position - self.position
        distance = length(direction)

        if distance < self.arriveRadius:
            self.velocity = np.array([0, 0])
            return result
        elif distance > self.arriveSlow:
            targetSpeed = self.maxVelocity
        else:
            targetSpeed = self.maxVelocity * distance / self.arriveSlow

        targetVelocity = normalize(direction) * targetSpeed
        result.linear = (targetVelocity - self.velocity) / self.arriveTime

        if length(result.linear) > self.maxLinear:
            result.linear = normalize(result.linear) * self.maxLinear

        result.angular = 0
        return result

# Define a class to represent a character that follows a path
class FollowPath(Character):
    def __init__(self, path, pathOffset=1.0):
        super().__init__()
        self.path = path
        self.pathOffset = pathOffset
        self.currentParam = 0.0
        
    # Define a method to get the steering output for the follow path behavior
    def getSteering(self):
        # Get the closest parameter on the path
        self.currentParam = Path.getParam(self.path, self.position)

        # Move along the path by pathOffset
        targetParam = min(1, self.currentParam + self.pathOffset)

        # Get the target position on the path
        targetPosition = Path.getPosition(self.path, targetParam)

        # Create a temporary target character at the target position
        target = Character()
        target.position = targetPosition

        # Use seek behavior to move toward the target
        return self.getSteeringSeek(target)

# Initialize the path
path_1_x = [0, -20, 20, -40, 40, -60, 60, 0]
path_1_y = [90, 65, 40, 15, -10, -35, -60, -85]
path_1 = Path.assemble(2701, path_1_x, path_1_y)  # Create path

# Initialize the character with follow path behavior
character_2701 = FollowPath(path=path_1, pathOffset=0.04)
character_2701.ID = 2701
character_2701.steer = FOLLOW_PATH  
character_2701.position = np.array([20, 95])
character_2701.maxVelocity = 4
character_2701.maxLinear = 2
character_2701.path = path_1
character_2701.pathOffset = 0.04

# Store the character in a list
characters = [character_2701]

# Store the path in a list
paths = [path_1]

# Define simulation parameters
delta_time = 0.50  # Duration of time step
stop_time = 125  # Time of last time step
check_collisions = False  # Collision detection flag

# Write the initial states to a file
with open('output.txt', 'w') as f:
    for character in characters:
        print(time, character.ID, character.position[0], character.position[1], character.velocity[0], character.velocity[1], character.linear[0], character.linear[1],
              character.orientation, character.steer, character.colCollided, sep=",", file=f)

# Run the simulation
while time < stopTime:
    time += deltaTime

    # Update each character's state
    for character in characters:
        if character.steer == CONTINUE:
            steering = character.getSteeringContinue()
        elif character.steer == SEEK:
            steering = character.getSteeringSeek(character.target)
        elif character.steer == FLEE:
            steering = character.getSteeringFlee(character.target)
        elif character.steer == ARRIVE:
            steering = character.getSteeringArrive(character.target)
        elif character.steer == FOLLOW_PATH:
            # Get the steering output for the follow path behavior
            steering = character.getSteering()
        
        # Update the character's state
        character.update(steering, deltaTime)

    # Write the updated states to a file
    with open('output.txt', 'a') as f:
        for character in characters:
            print(time, character.ID, character.position[0], character.position[1], character.velocity[0], character.velocity[1], character.linear[0], character.linear[1],
              character.orientation, character.steer, character.colCollided, sep=",", file=f)
