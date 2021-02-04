
//-------------------------------------------------------------
// variables required for this simulation
//-------------------------------------------------------------
double Vm;       // Magnitude of muzzle velocity, m/s
double Alpha;    // Angle from y-axis (upward) to the cannon.
                 // When this angle is zero the cannon is pointing
                 // straight up, when it is 90 degrees, the cannon
                 // is horizontal
double Gamma;    // Angle from x-axis, in the x-z plane to the cannon.
                 // When this angle is zero the cannon is pointing in
                 // the positive x-direction, positive values of this angle
                 // are toward the positive z-axis
double L;        // This is the length of the cannon, m
double Yb;       // This is the base elevation of the cannon, m

double X;        // The x-position of the center of the target, m
double Y;        // The y-position of the center of the target, m
double Z;        // The z-position of the center of the target, m
double Length;   // The length of the target measured along the x-axis, m
double Width;    // The width of the target measured along the z-axis, m
double Height;   // The height of the target measure along the y-axis, m

struct Vector    // The shell position (displacement) vector in 3D (i,j,k)
{
   double i;
   double j;
   double k;
} pos;

double time;     // The time from the instant the shell leaves the cannon, seconds
double tInc;     // The time increment to use when stepping through the simulation, seconds

double g;        // acceleration due to gravity, m/s^2

void initialize_variables();
void print_initial_conditions();
void print_projectile();
int step_simulation();
