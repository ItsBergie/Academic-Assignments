# CS330 Programming Assignment 1, SEEK, FLEE, and ARRIVE
# Eli Berg
# Email: erb0023@uah.edu

import math

# Define the Character class to represent a character in the simulation
class Character:
    def __init__(self, char_id, behavior, position, velocity, orientation, max_velocity, max_acceleration, target=None, arrival_radius=0, slowing_radius=0, time_to_target=1):
        # Initialize character attributes
        self.char_id = char_id  # Unique identifier for the character
        self.behavior = behavior  # Behavior type
        self.position = list(map(float, position))  # Current position [x, y]
        self.velocity = list(map(float, velocity))  # Current velocity [vx, vy]
        self.orientation = orientation  # Current orientation (angle)
        self.max_velocity = max_velocity  # Maximum speed the character can achieve
        self.max_acceleration = max_acceleration  # Maximum acceleration
        self.target = target  # Target character (if any)
        self.arrival_radius = arrival_radius  # Radius for arriving at the target
        self.slowing_radius = slowing_radius  # Radius for slowing down
        self.time_to_target = time_to_target  # Time to reach the target
        self.acceleration = [0.0, 0.0]  # Current acceleration [ax, ay]
    
    def update(self, dt):
        # Update the character's state based on the time step (dt)
        self.apply_steering_behavior()  # Apply the appropriate steering behavior
        self.update_position(dt)  # Update the position based on velocity
        self.update_velocity(dt)  # Update the velocity based on acceleration
        self.limit_velocity()  # Ensure velocity does not exceed max_velocity
    
    def apply_steering_behavior(self):
        # Apply the steering behavior based on the character's behavior type
        if self.behavior == "Seek":
            self.seek()  # Move towards the target
        elif self.behavior == "Flee":
            self.flee()  # Move away from the target
        elif self.behavior == "Arrive":
            self.arrive()  # Move towards the target and slow down upon arrival
    
    def update_position(self, dt):
        # Update the position using the current velocity and time step
        self.position[0] += self.velocity[0] * dt
        self.position[1] += self.velocity[1] * dt
    
    def update_velocity(self, dt):
        # Update the velocity using the current acceleration and time step
        self.velocity[0] += self.acceleration[0] * dt
        self.velocity[1] += self.acceleration[1] * dt
    
    def limit_velocity(self):
        # Limit the velocity to the maximum allowed speed
        speed = math.hypot(self.velocity[0], self.velocity[1])
        if speed > self.max_velocity:
            scale = self.max_velocity / speed
            self.velocity[0] *= scale
            self.velocity[1] *= scale
    
    def seek(self):
        # Calculate the direction to the target and set acceleration accordingly
        direction = self.calculate_direction_to_target()
        distance = math.hypot(direction[0], direction[1])
        if distance > 0:
            direction = [d / distance * self.max_acceleration for d in direction]
            self.acceleration = direction
    
    def flee(self):
        # Calculate the direction away from the target and set acceleration accordingly
        direction = self.calculate_direction_from_target()
        distance = math.hypot(direction[0], direction[1])
        if distance > 0:
            direction = [d / distance * self.max_acceleration for d in direction]
            self.acceleration = direction
    
    def arrive(self):
        # Calculate the direction to the target and adjust speed based on distance
        direction = self.calculate_direction_to_target()
        distance = math.hypot(direction[0], direction[1])
        
        # Adjust speed based on distance to the target
        if distance < self.arrival_radius:
            arrive_speed = 0  # Stop if within arrival radius
        elif distance > self.slowing_radius:
            arrive_speed = self.max_velocity  # Move at max speed if outside slowing radius
        else:
            arrive_speed = self.max_velocity * (distance / self.slowing_radius)  # Slow down proportionally
        
        # Calculate the desired velocity and acceleration
        arrive_velocity = [d / distance * arrive_speed for d in direction]
        self.acceleration = [(arrive_velocity[0] - self.velocity[0]) / self.time_to_target,
                             (arrive_velocity[1] - self.velocity[1]) / self.time_to_target]
        
        # Limit acceleration to the maximum allowed
        acc_distance = math.hypot(self.acceleration[0], self.acceleration[1])
        if acc_distance > self.max_acceleration:
            scale = self.max_acceleration / acc_distance
            self.acceleration = [a * scale for a in self.acceleration]
    
    def calculate_direction_to_target(self):
        # Calculate the direction vector from the character to the target
        return [self.target.position[0] - self.position[0], self.target.position[1] - self.position[1]]
    
    def calculate_direction_from_target(self):
        # Calculate the direction vector from the target to the character
        return [self.position[0] - self.target.position[0], self.position[1] - self.target.position[1]]

# Function to initialize a list of characters with predefined attributes
def initialize_characters():
    return [
        Character(2601, "Continue", [0, 0], [0, 0], 0, 0, 0),  # Stationary character
        Character(2603, "Seek", [-50, 40], [0, 8], 3*math.pi/2, 8, 2),  # Seeker character
        Character(2602, "Flee", [-30, -50], [2, 7], math.pi/4, 8, 1.5),  # Fleeing character
        Character(2604, "Arrive", [50, 75], [-9, 4], math.pi, 10, 2, arrival_radius=4, slowing_radius=32, time_to_target=1)  # Arriving character
    ]

# Function to set the target for characters with "Seek", "Flee", or "Arrive" behaviors
def set_targets(characters):
    target = characters[0]  # Set the first character as the target
    for char in characters:
        if char.behavior in ["Seek", "Flee", "Arrive"]:
            char.target = target

# Function to simulate the movement of characters over time and write results to a file
def simulate(characters, dt, steps, output_file):
    with open(output_file, "w") as file:
        for t in range(steps + 1):
            for char in characters:
                # Write the current state of the character to the file
                file.write(f"{t*dt},{char.char_id},{char.position[0]},{char.position[1]},{char.velocity[0]},{char.velocity[1]},{char.acceleration[0]},{char.acceleration[1]},{char.orientation},{6 if char.behavior == 'Seek' else 7 if char.behavior == 'Flee' else 8 if char.behavior == 'Arrive' else 1},FALSE\n")
                char.update(dt)  # Update the character's state

# Main function to run the simulation
def main():
    dt = 0.5  # Time step for the simulation
    steps = 100  # Number of steps to simulate
    output_file = "data.txt"  # Output file to store simulation results
    
    characters = initialize_characters()  # Initialize characters
    set_targets(characters)  # Set targets for characters
    simulate(characters, dt, steps, output_file)  # Run the simulation

# Entry point for the script
if __name__ == "__main__":
    main()