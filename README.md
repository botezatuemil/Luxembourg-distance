
# Luxembourg distance with Dijkstra

This project renders a map of Luxembourg and shows the shortest distance between 2 clicked points




## How it works?

- A text file stores the real coordinates of the Luxemburg, a file with 40000 nodes.
- The data is readed and scaled to window screen dimensions

![Luxemburg](https://user-images.githubusercontent.com/74835450/195405438-9a9a6c1e-167e-443b-bd44-7b328bc29e60.jpg)

- When a user clicks a point, it receives the closest node from his cursor
- The Dijkstra algorithm is used to calculate and mark the distance between the points
- The arch between the traversed nodes is marked with red

![LuxemburgDistance](https://user-images.githubusercontent.com/74835450/195405450-0780c8b2-cad3-40bb-a1d0-831844d01817.jpg)

## Tech Stack

C++ with Qt widgets for interface

