/**
 * @file util.h
 * @author y.qiu (y.qiu@pixoel.com)
 * @brief
 * @version 0.1
 * @date 2022-02-16
 *
 * Copyright (c) 2021 Pixoel Technologies Co.ltd.
 *
 */

#pragma once

#include "type.h"

namespace ppf {

std::vector<std::size_t> samplePointCloud(const ppf::PointCloud &pc, float sampleStep,
                                          KDTree *kdtree = nullptr);

PointCloud extraIndices(const ppf::PointCloud &pc, const std::vector<std::size_t> &indices);

void normalizeNormal(ppf::PointCloud &pc);

BoundingBox computeBoundingBox(const ppf::PointCloud &pc);

PointCloud transformPointCloud(const ppf::PointCloud &pc, const Eigen::Matrix4f &pose);

std::vector<Eigen::Vector3f> estimateNormal(const ppf::PointCloud &pc);

std::vector<Eigen::Vector3f> estimateNormal(const ppf::PointCloud &pc, const ppf::PointCloud &ref);

Eigen::Matrix4f transformRT(const Eigen::Vector3f &p, const Eigen::Vector3f &n);

float computeAlpha(const Eigen::Vector3f &p1, const Eigen::Vector3f &p2, const Eigen::Vector3f &n1);

inline Eigen::Matrix4f XRotMat(float angle) {
    Eigen::Matrix4f T;
    T << 1, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1;

    return T;
}

std::vector<std::vector<Pose>> clusterPose(const std::vector<Pose> &poseList,
                                           float distanceThreshold, float angleThreshold);

/**
 * @brief cluster by overlap
 *
 * @param poseList
 * @param pos
 * @param threshold
 * @return std::vector<Pose>
 */
std::vector<Pose> clusterPose2(std::vector<Pose> &poseList, Eigen::Vector3f &pos, float threshold);

std::vector<Pose> sortPoses(std::vector<Pose> poseList);

std::vector<Pose> avgClusters(const std::vector<std::vector<Pose>> &clusters);

PointCloud loadText(const std::string &filename);

void saveText(const std::string &filename, const PointCloud &pc);

void findClosestPoint(const KDTree &kdtree, const PointCloud &srcPC, std::vector<int> &indices,
                      std::vector<float> &distances);

std::vector<uint32_t> computePPF(const Eigen::Vector3f &p1, const Eigen::Vector3f &n1,
                                 const std::vector<Eigen::Vector3f> &p2,
                                 const std::vector<Eigen::Vector3f> &n2, float angleStep,
                                 float distStep);

} // namespace ppf