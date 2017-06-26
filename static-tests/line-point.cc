// reference to stackoverflow

/*
  Here's some correct code, in C++. It presumes a class 2D-vector class vec2 {float x,y;}, essentially, with operators to add, subract, scale, etc, and a distance and dot product function (i.e. x1 x2 + y1 y2).
*/

float minimum_distance(vec2 v, vec2 w, vec2 p) {
  // Return minimum distance between line segment vw and point p
  const float l2 = length_squared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
  if (l2 == 0.0) return distance(p, v);   // v == w case
  // Consider the line extending the segment, parameterized as v + t (w - v).
  // We find projection of point p onto the line.
  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
  // We clamp t from [0,1] to handle points outside the segment vw.
  const float t = max(0, min(1, dot(p - v, w - v) / l2));
  const vec2 projection = v + t * (w - v);  // Projection falls on the segment
  return distance(p, projection);
}



function pDistance(x, y, x1, y1, x2, y2) {

  var A = x - x1;
  var B = y - y1;
  var C = x2 - x1;
  var D = y2 - y1;

  var dot = A * C + B * D;
  var len_sq = C * C + D * D;
  var param = -1;
  if (len_sq != 0) //in case of 0 length line
    param = dot / len_sq;

  var xx, yy;

  if (param < 0) {
    xx = x1;
    yy = y1;
  }
  else if (param > 1) {
    xx = x2;
    yy = y2;
  }
  else {
    xx = x1 + param * C;
    yy = y1 + param * D;
  }

  var dx = x - xx;
  var dy = y - yy;
  return Math.sqrt(dx * dx + dy * dy);
}
