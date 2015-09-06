# Smart-Interactive-Maps-SIM-
The project is about building a system that allows users to find a route on the screen around public place by pointing gestures.
There are three modules in this system:
# Camera Calibration:
The purpose: We need to automatically synchronize the map on the screen with the map captured from the camera.
The direction of solving: 
  - Observation: instead of being rectangular, the map on the screen will become trapezoid or quadrilateral. The shape depends on the angle of the camera compared to the screen for interaction.
  - Solution:
    + Using SIFT features for matching the keypoints from the image of map on the screen to the keypoints of the map on the map captured from camera.
    + Based on matched pair of keypoints, we estimate the homography matrix used for tranforming a coordinate on map into a correspondent coordinate on the map captured from camera. The method of estimating this homography matrix is running RANSAC algorithm on a list of pair matched keypoints which are collected from SIFT matching.
    + By a simple geomtry tranformation with the homography matrix, we easily synchronize every point on the map of screen with every point on the map captured from camera.

# Background subtraction:
The purpose: Recognize the hand or pointing device appear on the camera for recognizing the control gestures of the user.
The direction of solving:
  - Observation: to recognize the pointing gestures, the system is required to distinguish between the static scene on the camera (background) and pointing gestures (foreground). Therefore, background subtraction is next problem for the system.
  - Solution:
    + Based on the small variation of RGB values of a pixel and gradual change of environment, we can solve this problem by using codebook method for subtracting the background - Reference: "Background modeling and subtraction by codebook construction", authors: Kyungnam Kim et al.
    + Codebook of each pixel which contains several codewords: contains RGB information of the pixel and 6-tuple (minimum brightness, maximum brightness, frequency, longest interval in which this codeword, first access, last access) will be trained through sequence of training images.

# Pointing Tip Detection:
The purpose: Localizing correctly the tip for tracking the control of the users.
The direction of solving:
  - Observation: to recognize the pointing tip, the authors defined the tips as a peak in hand geometry boundary. Therefore, we apply "peaks" and "valleys" theorem from the research of Jakub Segen and Senthil Kumar "Shadow Gestures: 3D Hand Pose Estimation using a Single Camera".
  - Solution:
    + Each point on the boundary, we consider change of two vector: one created from that point and its previous point and one created from that point and its next point in boundary.
    + By using characteristic of magnitude of cross product between two vectors, we can easily know that boundary point may be a peaks we need through several training stage for obtain a threshold to eliminate false peaks when selecting the peak.
