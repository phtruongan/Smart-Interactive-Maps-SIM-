# Smart-Interactive-Maps-SIM-
The project is about building a system that allows users to find a route on the screen around public place by pointing gestures.
There are three modules in this system:
# Camera Calibration:
The purpose: We need to automatically synchronize the map on the screen with the map captured from the camera.
The direction of solving: 
  - Observation: instead of being rectangular, the map on the screen will become trapezoid or quadrilateral. The shape depends on the angle of the camera compared to the screen for interaction.
  - Solution:
    + Using SIFT features for matching the keypoints from the image of map on the screen to the keypoints of the map on the map captured from camera.
    + 
# Background subtraction:
# Pointing Tip Detection:
