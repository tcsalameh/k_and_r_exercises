/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
  struct point temp;

  temp.x = x;
  temp.y = y;
  return temp;
}

struct rect screen;
struct point middle;
struct point makepoint(int, int);

screen.pt1 = makepoint(0, 0);
screen.pt2 = makepoint(XMAX, YMAX);
middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                   (screen.pt1.y + screen.pt2.y) / 2);

/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2)
{
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
  return p.x >= r.pt1.x && p.x < r.pt2.x
      && p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
  struct rect temp;

  temp.pt1.x = min(r.pt1.x, r.pt2.x);
  temp.pt1.y = min(r.pt1.y, r.pt2.y);
  temp.pt2.x = max(r.pt1.x, r.pt2.x);
  temp.pt2.y = max(r.pt1.y, r.pt2.y);
  return temp;
}

// passing a large struct to a function, use a pointer
// pp is pointer to a structure of type point
struct point origin, *pp;

pp = &origin;
printf("origin is (%d, %d)\n", (*pp).x, (*pp).y);

// alternative notation for structure pointers
// p->member-of-structure
// refers to a particular member where p is a pointer to the struct

printf("origin is (%d, %d)\n", pp->x, pp->y);

struct rect r, *rp = &r;

// all four of these are the same
// r.pt1.x
// rp->pt1.x
// (r.pt1).x
// (rp->pt1).x

// struct operators, (), and [] have highest precedence

struct {
  int len;
  char *str;
} *p;

// this increments len, NOT p, because -> takes precedence over addition
++p->len;

