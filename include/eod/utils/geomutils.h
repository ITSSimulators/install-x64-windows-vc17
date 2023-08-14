/*
    Copyright (C) 2008 Seeing Machines Ltd. All rights reserved.

    This file is part of the CoreData API.

    This file may be distributed under the terms of the SM Non-Commercial License
    Agreement appearing in the file LICENSE.TXT included in the packaging
    of this file.

    This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
    WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

    Further information about the CoreData API is available at:
    http://www.seeingmachines.com/

*/
#ifndef SM_COREDATA_EOD_GEOMUTILS_H
#define SM_COREDATA_EOD_GEOMUTILS_H

//! @file
#include "eod/utils/geomutilserror.h"

namespace sm
{
    namespace eod
    {
        namespace utils
        {
            /*!
                @name Geometry Utility Functions
            */
            //@{

            //! Indexes into arrays containing a pitch and yaw value
            enum 
            { 
                PITCH = 0,
                YAW = 1    
            };
        
            //! Indexes into arrays containing a 3D direction vector
            enum
            {
                X_AXIS = 0,
                Y_AXIS = 1,
                Z_AXIS = 2
            };
        
            //! Used to extract a direction vector from a rotation matrix in rotMatrixToDirection
            enum Direction
            {
                X_DIRECTION = 0,
                Y_DIRECTION = 1,
                Z_DIRECTION = 2
            };
        
            //! Scalar-vector multiplication operator for STL vectors of float
            SM_COREDATA_API const std::vector<float> operator*(float factor, const std::vector<float>& direction);
        
            //! Unary inversion operator for STL vectors of float
            SM_COREDATA_API const std::vector<float> operator-(const std::vector<float>& direction);
        
            //! Addition operator for STL vectors of float
            /*! @pre direction vectors must have the same number of dimensions
             */
            SM_COREDATA_API const std::vector<float> operator+(const std::vector<float>& direction1, const std::vector<float>& direction2);
        
            //! Subtraction operator for STL vectors of float
            /*! @pre direction vectors must have the same number of dimensions
             */
            SM_COREDATA_API const std::vector<float> operator-(const std::vector<float>& direction1, const std::vector<float>& direction2);
    
            //! Construct a quaternion from a vector containing euler angles
            /*! @param euler_angles in the convention XYZ
                @return The Quaternion [q0, q1, q2, q3] 
                @pre euler angle must be of 3 dimensions
             */
           SM_COREDATA_API dStdVector4 fromEulerAngles(const dStdVector3& euler_angles);
    
            //! Construct a quaternion from a vector containing quaternion components
            /*! @param quaternion components in the convention [q0, q1, q2, q3]
                @return The euler_angles in the convention XYZ 
                @pre quaternion must have 4 elements
             */
            SM_COREDATA_API dStdVector3 toEulerAngles(const dStdVector4& quaternion);

            //! @return The inner product of the two direction vectors
            /*! @pre direction vectors must have the same number of dimensions
             */
            SM_COREDATA_API float innerProduct(const std::vector<float>& direction1, const std::vector<float>& direction2);
    
            //! @return The cross product of the two vectors passed in
            /*! @pre direction vectors are of 3 dimensions
             */
            SM_COREDATA_API const fStdVector3 crossProduct(const fStdVector3& direction1, const fStdVector3& direction2);
    
            //! @return The Cartesian length of a vector
            SM_COREDATA_API float length(const std::vector<float>& direction);
    
            //! Unit vector
            /*! @return The normalized vector of a given vector
                @pre direction has a length 0.0 */
            SM_COREDATA_API const std::vector<float> unitVector(const std::vector<float>& direction);
    
            //! @return a vector of length 2 containing [PITCH,YAW] angles in radians, computed from
            //! the 3D direction vector [X, Y, Z] @a direction.
            /*! @param direction Direction vector in some coordinate 
                @note this function always uses the negative z convention 
                @pre direction vector must be in 3 dimensions */
            SM_COREDATA_API const fStdVector2 pitchYawFromDirection(const fStdVector3& direction);
    
            //! @return a normalized vector [X, Y, Z] in the direction given by the [PITCH, YAW] angles in @a pitch_yaw.
            /*! @param pitch_yaw The pitch and yaw angles in some coordinate frame. Pitch corresponds to element 0.
                @note this function always uses the negative z convention 
                @pre pitch_yaw must have two elements */
            SM_COREDATA_API const fStdVector3 directionFromPitchYaw(const fStdVector2& pitch_yaw);
    
            //! Calculates the coefficients for the ray's basis vectors for the points of closest approach 
            /*! @param origin1 The origin of the first ray [X, Y, Z]
                @param direction1 The direction vector of the first ray [X, Y, Z]
                @param origin2 The origin of the second ray [X, Y, Z]
                @param direction2 The direction vector of the second ray [X, Y, Z]
                @param coefficient1_out Return the coefficient for ray1 for point of closest approach 
                @param coefficient2_out Return the coefficient for ray2 for point of closest approach 
                @pre origin1, direction1, origin2, direction2 must be in 3 dimensions
                @throw GeomUtilsError if the two rays are parallel */
            SM_COREDATA_API void coefficientsOfRaysClosestApproach(
                const fStdVector3& origin1, const fStdVector3& direction1,
                const fStdVector3& origin2, const fStdVector3& direction2,
                float& coefficient1_out, float& coefficient2_out);
    
            //! Calculates the points of closest approach on the rays 
            /*! @param origin1 The origin of the first ray [X, Y, Z]
                @param direction1 The direction vector of the first ray [X, Y, Z]
                @param origin2 The origin of the second ray [X, Y, Z]
                @param direction2 The direction vector of the second ray [X, Y, Z]
                @param closest_point1_out Returns the closest point on ray1 to ray2
                @param closest_point2_out Returns the closest point on ray2 to ray1
                @pre origin1, direction1, origin2, direction2 must be in 3 dimensions
                @throw GeomUtilsError if the two rays are parallel */
            SM_COREDATA_API void pointsOfRaysClosestApproach(
                const fStdVector3& origin1, const fStdVector3& direction1,
                const fStdVector3& origin2, const fStdVector3& direction2,
                fStdVector3& closest_point1_out, fStdVector3& closest_point2_out);
     
            //! Calculates the intersection of two rays, or the point in the middle between the two closest points
            /*! @param origin1 The origin of the first ray [X, Y, Z]
                @param direction1 The direction vector of the first ray [X, Y, Z]
                @param origin2 The origin of the second ray [X, Y, Z]
                @param direction2 The direction vector of the second ray [X, Y, Z]
                @return the 3D intersection point, or the point in the middle of the line joining the
                closest points on each ray
                @pre origin1, direction1, origin2, direction2 must be in 3 dimensions
                @throw GeomUtilsError if the two rays are parallel */
            SM_COREDATA_API const fStdVector3 rayIntersectionPoint(
                const fStdVector3& origin1, const fStdVector3& direction1,
                const fStdVector3& origin2, const fStdVector3& direction2);
    
            //! Calculate the angle between two direction vectors.
            /*! @param direction1 First direction vector [X, Y, Z]
                @param direction2 Second direction vector [X, Y, Z]
                @note this angle is always positive. It is not signed
                @return The angle between the two vectors (in radians)
                @pre direction vectors must be in 3 dimensions
                @throw GeomUtilsError if one of the vectors is of length 0
            */
            SM_COREDATA_API float vectorIntersectionAngle(
                const fStdVector3& direction1, const fStdVector3& direction2);
    
            //! Convert from a set of euler angles to a 3x3 rotation matrix
            /*! @param euler_angles The three euler angles defining the rotation. Assumes that the order of rotation
                around the axes is [X, Y, Z] 
                @return 3x3 rotation matrix defining the rotation. When accessing this matrix, the first index is the
                row index, the second is the column index
                @pre euler_angles must be in 3 dimensions
             */
            SM_COREDATA_API std::vector< std::vector<float> > eulerAnglesToRotationMatrix(
                const fStdVector3& euler_angles);
    
            //! Convert from a 3x3 rotation matrix to a set of euler angles
            /*! @param rotation_matrix 3x3 rotation matrix defining the rotation. The first index of the matrix should
                be the row index, the second is the column index
                @return The vector of three euler angles defining the rotation. The order of rotation around the axes is 
                [X, Y, Z] 
                @pre rotation matrix must be 3x3 
             */
            SM_COREDATA_API fStdVector3 rotMatrixToEulerAngles(const std::vector< std::vector<float> >& rotation_matrix);
    
            //! Extract the direction vector for an axis from the rotation matrix
            /*! This is the direction of the \a dir axis rotated by \a rotation_matrix
                @note the indexes of rotation_matrix assume that the first index refers to the row, the second
                index to the column */
            SM_COREDATA_API std::vector<float> rotMatrixToDirection(std::vector< std::vector<float> > rotation_matrix, Direction dir);
    
            //! Calculate the point where a ray intersects with a plane
            /*! The plane is defined by three corner points (top-left, top_right and bottom-left).
                These points define the coordinate frame of the plane. The origin is at the top-left
                corner. The positive x axis points from the origin towards the top-right corner.
                The positive y axis points from the origin towards the bottom-left corner.
                The coordinate values are normalised, so that the top-right corner is at (1, 0), 
                and the bottom-left corner is at (0, 1).
                @note This function will report a plane intersection even if the intersection point
                is not within the boundaries defined by the three corner points. To check if the intersection
                occurs within the boundaries of the three corner points, check if the plane_intersect value
                is within the rectangle defined by (0, 0), (0, 1), (1, 0), (1, 1).
                @param ray_origin Origin of the ray in world coordinates [X, Y, Z]
                @param direction Direction vector of the ray in world coordinates [X, Y, Z]
                @param plane_top_left top-left-hand corner of the plane
                @param plane_top_right top-right-hand corner of the plane
                @param plane_bottom_left bottom_left-hand corner of the plane
                @param plane_intersect Receives the intersection point in normalised plane coordinates
                @param world_intersect Recieves the intersection point in world coordinates
                @return true if the ray intersects the plane, false otherwise. A ray does not intersect the 
                plane if it is parallel, or if its direction vector points away from the plane */
            SM_COREDATA_API bool rayPlaneIntersect(
                const fStdVector3& ray_origin, 
                const fStdVector3& direction, 
                const fStdVector3& plane_top_left, 
                const fStdVector3& plane_top_right,
                const fStdVector3& plane_bottom_left, 
                fStdVector2& plane_intersect,
                fStdVector3&  world_intersect);
            //@}
        }
    }
}

#endif

