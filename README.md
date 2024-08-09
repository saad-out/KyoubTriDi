# 3D Raycasting Engine
 This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. our goal will be to make a dynamic view inside a maze, in which you'll have to find our way. 

 ## Overview
 This project is a 3D raycasting engine implemented in C, inspired by classic games like Wolfenstein 3D. It showcases how a simple 2D grid map can be transformed into a 3D perspective by using the raycasting technique. The player can move around a map, interact with the environment, and experience a 3D representation of a 2D space.

 ## Features
- 2D Grid Map to 3D Conversion: The game renders a 3D environment based on a 2D grid map, where each cell represents a wall, floor, or door.
- Realistic Wall Rendering: Walls are textured and rendered with perspective correction, minimizing distortion and enhancing realism.
- Player Movement and Rotation: The player can move forward, backward, and rotate left or right, changing their viewpoint dynamically.
- Minimap: A minimap shows the player's position and surrounding environment, with a portion of the map centered around the player.
- Interactive Doors: Doors can be opened and closed using the O key, allowing for dynamic interaction with the environment.

  ![alt text](https://github.com/saad-out/KyoubTriDi/blob/main/images/screen1.png)
    ![alt text](https://github.com/saad-out/KyoubTriDi/blob/main/images/screen2.png)

## How It Works
### Raycasting Algorithm
Raycasting is the core technique used in this engine. It involves casting rays from the player’s viewpoint and calculating where these rays intersect with walls in the 2D grid map. The distance from the player to these intersections determines the height of the walls to be rendered on the screen, creating a 3D illusion.

1- Ray Generation:

- For each column of pixels on the screen, a ray is cast at an angle relative to the player's view direction.
- The angle of each ray is adjusted based on the field of view (FOV).

2- Ray-Grid Intersection:
- The rays are checked against the grid map to find horizontal and vertical intersections with walls.
- The intersection closest to the player is chosen, determining the distance to the wall.

3- Wall Rendering:
- The distance to the intersection is used to calculate the height of the wall slice to be rendered.
- Textures are mapped onto the walls using the calculated intersection points to determine the correct texture coordinates.

4- Minimap Rendering:
- A small section of the map around the player is displayed, with the player centered.
- The minimap updates as the player moves, giving a real-time view of their surroundings.

### Player Movement and Interaction
1- Movement:
- The player moves based on the direction they are facing, with their position updated using trigonometric calculations.
- Collision detection prevents the player from passing through walls.

2- Rotation:
- The player can rotate left or right, changing the angle of the rays cast and thus the view direction.

3- Door Interaction:
- Doors are represented as D in the map. When the player is near a door and facing it, pressing the O key opens or closes the door.

### Texturing
Textures are applied to walls to enhance the visual experience. The texture mapping ensures that the correct portion of the texture is displayed based on the wall's position and the player's viewpoint. Special care is taken to minimize pixelation, ensuring that textures appear smooth even when viewed at different distances.

## Conclusion
This raycasting engine demonstrates the power of simple algorithms to create complex visual effects. The project provides a foundational understanding of 3D rendering techniques and interactive game mechanics, offering ample opportunities for further development and enhancement.
