# MORPH: The Module Orientated Robotic Platform For Hybridisation

## Background

The last decade has seen the rapid advancement of quadruped robots such as Spot from Boston Dynamics and Stanford Doggo, which key examples that achieve advanced automation and fine motor control.

Despite their success, current quadruped robots are still plagued by two key limitations. The first of these is wear and tear of components due to impact forces and repetitive stresses. These external forces degrade components, often resulting in failure and requiring complex maintenance to fix.

Along with mechanical fatigue, most commercial robots lack reconfigurability. Current robots come in a standard ‘one-size-fits-all’ configuration, requiring different models or robots to be purchased for alternate functionalities. For instance, you may require a narrow robot for inspection tasks in tight places, as well as a separate robot with a wide base for hauling large loads.

<p align="center">
  <img width="565" height="420" alt="Stanford Doggo" src="https://github.com/user-attachments/assets/36c6825d-523f-4d1c-abaa-1eb78a7fda20" />
  <p align="center"><strong>Stanford Doggo</strong></p>
</p>

## Scope of Work

The aim for this project was to design, implement and test a quadruped robot capable of traversing terrain such as grass or pavement. 

The robot must directly address reconfigurability and ease of maintenance by implementing a modular architecture, whilst simplifying other elements where possible. Features such as Autonomy, perception, accessory development and long-term deployment are out of scope for this project.

# Modularity

The integration of modularity forms a core component of this project and consists of two stages: component modularity and operational modularity. On this slide we refer to component modularity which aims to standardise the mechanical framework of the robot. This modular system consists of a singular cubic unit made up of a wire frame and faceplates. The wire frames allow for the attachment of face plates via heat-set inserts and M3 bolts.

The most important face plate variant is the standardised connector assembly. This assembly includes:
* Four magnets in each corner, such that each diagonal poles are in the same orientation.
* The plate also contains 4 bi-gendered pin-hole mechanisms for alignment.
* On the backside of the assembly there is room for a lock and key mechanism to hold the custom electrical connector in place.
* The custom electrical connector has a total of 12 pins arranged in four groups of 3. Much like the other components, these are identical about the diagonals.

The symmetry of the connector is critical to allow identical assemblies to connect on either side of the module. When one connector is rotated, it essentially becomes mirrored about a vertical axis, allowing opposing gendered or poled connectors to join successfully.

<p align="center">
  <img width="796" height="603" alt="image" src="https://github.com/user-attachments/assets/3430d8e8-4603-4960-a343-6d09dc1b43b8" />
  <p align="center"><strong>Wire Frame</strong></p>
</p>

<p align="center">
  <img width="320" height="412" alt="image" src="https://github.com/user-attachments/assets/f001ea27-8fa3-4de9-8263-87126185e1c1" />
  <img width="301" height="412" alt="image" src="https://github.com/user-attachments/assets/3f8e1010-1bd5-4ccd-af00-b5d92d372b03" />
  <p align="center"><strong>Connection Plate Assembly</strong></p>
</p>

Operational modularity in this project separates modules into their operational functions. These modules are formed by a lattice of standardised units constructed in the component modularity stage. The operational models include:
* An electronics module that houses the power system, sensors and microcontroller.
* An actuator module consisting of an individual leg mechanism and actuators.
* And a spacer module that allows for configuration to occur without gaps in the lattice.

These modules allow for a variety of arrangements of the robot, including the two on screen and can even accommodate up to eight actuator modules.

<p align="center">
  <img width="527" height="412" alt="image" src="https://github.com/user-attachments/assets/0008ee7b-8857-40bb-90d2-34c59ca4f2c0" />
  <p align="center"><strong>Electronics Module</strong></p>
</p>

<p align="center">
  <img width="509" height="413" alt="image" src="https://github.com/user-attachments/assets/927227e1-7e46-4ca0-b897-0c94f78072a0" />
  <p align="center"><strong>Spacer Module</strong></p>
</p>

<p align="center">
  <img width="431" height="412" alt="image" src="https://github.com/user-attachments/assets/ceb03295-fddb-4f81-a3f5-f81e772fa7a9" />
  <p align="center"><strong>Actuator Module</strong></p>
</p>

<p align="center">
  <img width="547" height="370" alt="image" src="https://github.com/user-attachments/assets/06835810-534c-483f-9c01-589e5002cdb5" />
  <p align="center"><strong>Square Configuration</strong></p>
</p>

<p align="center">
  <img width="431" height="370" alt="image" src="https://github.com/user-attachments/assets/17e8946e-de47-438f-872e-e8c16d7f8610" />
  <p align="center"><strong>Rectangle Configuration</strong></p>
</p>

## Electronics

<p align="center">
  <img width="1474" height="991" alt="image" src="https://github.com/user-attachments/assets/7a8be4dc-c09d-47d4-aa93-f3215d3073f7" />
  <p align="center"><strong>Schematic Diagram</strong></p>
</p>

## Control System

<p align="center">
  <img width="1461" height="683" alt="image" src="https://github.com/user-attachments/assets/4b773526-731e-43d3-9d69-8ca019f031fc" />
  <p align="center"><strong>Control System Flow of Logic</strong></p>
</p>
