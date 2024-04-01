// Copyright 2024 Borisov Saveliy
#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "core/task/include/task.hpp"

struct Point {
  int x, y;

  Point() = default;
  Point(const Point&) = default;
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  Point& operator=(const Point&) = default;

  bool operator==(const Point& other) const { return (x == other.x) && (y == other.y); }

  bool operator!=(const Point& other) const { return !(*this == other); }
};

class ConvexHullSequential : public ppc::core::Task {
 public:
  explicit ConvexHullSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  uint8_t *input, *output;
  int height, width;
  std::vector<uint8_t> image;
  std::vector<Point> points;
  void convexHullImage();

  static std::vector<Point> convertToPoints(const std::vector<uint8_t>& _image, int _height, int _width);
  std::vector<int> convertToImageVector(const std::vector<Point>& _points, int _height, int _width);

  static int isLeft(const Point& p1, const Point& p2, const Point& point);
  static bool isCollinear(const Point& p1, const Point& p2, const Point& p3);
  bool isOnSegment(const Point& p1, const Point& p2, const Point& point);
  int windingNumber(const std::vector<Point>& polygon, const Point& point);
  bool isInside(const std::vector<Point>& convexHull, const Point& point);
  static bool pointIsToTheRight(const Point& previous, const Point& current, const Point& potential);
};
