//
// Created by William DeVore on 3/29/16.
//

#ifndef RANGERBETA_RECTANGLE_H
#define RANGERBETA_RECTANGLE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

namespace Ranger {
    // Forward template declaration
    template<typename T>
    class Vector3;

    template<typename T>
    class Rectangle {
    public:
        T x, y;
        T width, height;

        Rectangle() = default;
        virtual ~Rectangle() = default;

        /** Constructs a new rectangle with the given corner point in the bottom left and dimensions.
         * @param x The corner point x-coordinate
         * @param y The corner point y-coordinate
         * @param width The width
         * @param height The height */
        Rectangle(T x, T y, T width, T height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        /** Constructs a rectangle based on the given rectangle
         * @param rect The rectangle */
        Rectangle(const Rectangle<T> &rect) {
            x = rect.x;
            y = rect.y;
            width = rect.width;
            height = rect.height;
        }

        /** @param x bottom-left x coordinate
         * @param y bottom-left y coordinate
         * @param width width
         * @param height height
         * @return this rectangle for chaining */
        Rectangle<T> &set(T x, T y, T width, T height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;

            return *this;
        }

        /** Sets the width and height of this rectangle
         * @param width The width
         * @param height The height
         * @return this rectangle for chaining */
        Rectangle<T> &setSize(T width, T height) {
            this->width = width;
            this->height = height;

            return *this;
        }

        /** Sets the squared size of this rectangle
         * @param sizeXY The size
         * @return this rectangle for chaining */
        Rectangle<T> &setSize(T sizeXY) {
            this->width = sizeXY;
            this->height = sizeXY;

            return *this;
        }

        /** @return the Vector3 with size of this rectangle. Z is 0.0.
         * @param size The Vector3 */
        Vector3<T> &getSize(Vector3<T> &size) {
            return size.set(width, height, 0);
        }

        /** @param x point x coordinate
         * @param y point y coordinate
         * @return whether the point is contained in the rectangle */
        bool contains(T x, T y) {
            return this->x <= x && this->x + this->width >= x && this->y <= y && this->y + this->height >= y;
        }

        /** @param point The coordinates vector
         * @return whether the point is contained in the rectangle */
        bool contains(const Vector3<T> &point) {
            return contains(point.x, point.y);
        }

        /** @param rectangle the other {@link Rectangle}.
         * @return whether the other rectangle is contained in this rectangle. */
        bool contains(const Rectangle<T> &rectangle) {
            T xmin = rectangle.x;
            T xmax = xmin + rectangle.width;

            T ymin = rectangle.y;
            T ymax = ymin + rectangle.height;

            return ((xmin > x && xmin < x + width) && (xmax > x && xmax < x + width))
                   && ((ymin > y && ymin < y + height) && (ymax > y && ymax < y + height));
        }

        /** @param r the other {@link Rectangle}
         * @return whether this rectangle overlaps the other rectangle. */
        bool overlaps(const Rectangle<T> &r) {
            return x < r.x + r.width && x + width > r.x && y < r.y + r.height && y + height > r.y;
        }

        /** Sets the values of the given rectangle to this rectangle.
         * @param rect the other rectangle
         * @return this rectangle for chaining */
        Rectangle<T> &set(const Rectangle<T> &rect) {
            this->x = rect.x;
            this->y = rect.y;
            this->width = rect.width;
            this->height = rect.height;

            return *this;
        }

        /** Merges this rectangle with the other rectangle. The rectangle should not have negative width or negative height.
         * @param rect the other rectangle
         * @return this rectangle for chaining */
        Rectangle<T> &merge(const Rectangle<T> &rect) {
            T minX = std::min(x, rect.x);
            T maxX = std::max(x + width, rect.x + rect.width);
            x = minX;
            width = maxX - minX;

            T minY = std::min(y, rect.y);
            T maxY = std::max(y + height, rect.y + rect.height);
            y = minY;
            height = maxY - minY;

            return *this;
        }

        /** Merges this rectangle with a point. The rectangle should not have negative width or negative height.
         * @param x the x coordinate of the point
         * @param y the y coordinate of the point
         * @return this rectangle for chaining */
        Rectangle<T> &merge(T x, T y) {
            T minX = std::min(this->x, x);
            T maxX = std::max(this->x + width, x);
            this->x = minX;
            this->width = maxX - minX;

            T minY = std::min(this->y, y);
            T maxY = std::max(this->y + height, y);
            this->y = minY;
            this->height = maxY - minY;

            return *this;
        }

        /** Merges this rectangle with a point. The rectangle should not have negative width or negative height.
         * @param vec the vector describing the point
         * @return this rectangle for chaining */
        Rectangle<T> &merge(const Vector3<T> &vec) {
            return merge(vec.x, vec.y);
        }

        /** Merges this rectangle with a list of points. The rectangle should not have negative width or negative height.
         * @param vecs the vectors describing the points
         * @return this rectangle for chaining */
        Rectangle<T> &merge(const std::vector<Vector3<T>> &vecs) {
            float minX = x;
            float maxX = x + width;
            float minY = y;
            float maxY = y + height;
            for (int i = 0; i < vecs.size(); ++i) {
                Vector3<T> v = vecs[i];
                minX = std::min(minX, v.x);
                maxX = std::max(maxX, v.x);
                minY = std::min(minY, v.y);
                maxY = std::max(maxY, v.y);
            }
            x = minX;
            width = maxX - minX;
            y = minY;
            height = maxY - minY;
            return *this;
        }

        /** Calculates the aspect ratio ( width / height ) of this rectangle
         * @return the aspect ratio of this rectangle. Returns Float.NaN if height is 0 to avoid ArithmeticException */
        T getAspectRatio() {
            return (height == 0) ? 0 : width / height;
        }

        /** Calculates the center of the rectangle. Results are located in the given Vector2
         * @param vector the Vector2 to use
         * @return the given vector with results stored inside */
        Vector3<T> &getCenter(Vector3<T> &vector) {
            vector.x = x + width / 2;
            vector.y = y + height / 2;
            return vector;
        }

        T area() {
            return width * height;
        }

        T perimeter() {
            return 2 * (width + height);
        }

    private:

        //! toString
        friend std::ostream &operator<<(std::ostream &os, const Rectangle<T> &t) {
            std::cout << std::fixed << std::setw(11) << std::setprecision(6);
            return os << "Rectangle: [" << t.x << ", " << t.y << ", " << t.width << " x " << t.height << "]";
        }
    };
}

#endif //RANGERBETA_RECTANGLE_H
