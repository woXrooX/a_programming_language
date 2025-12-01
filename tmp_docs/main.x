//// If-else statement
void check_value(int x) {
	if (x > 10) print("Value is greater than 10\n")
	else if (x == 10) print("Value is exactly 10\n")
	else print("Value is less than 10\n")
}

// While loop
void count_down(int start) {
	int i = start
	while (i > 0) {
		print(f"{i}\n", i)
		i = i - 1
	}

	print("Liftoff!\n")
}

// For loop
void print_numbers(int count) {
	for (int i = 0; i < count; i = i + 1) printf(f"{i}\n")
}


//// Basic function definition with traditional C syntax
int calculate_fibonacci(int n) {
	if (n <= 1) {
		return n
	}

	return calculate_fibonacci(n - 1) + calculate_fibonacci(n - 2)
}

//// Main function entry point
int main() {
	int result = calculate_fibonacci(10)
	print(f"Fibonacci(10) = {result}\n")

	return 0
}


// Simple class definition
class Point {
	// Member variables
	int x
	int y

	// Constructor
	void Point(int x_val, int y_val) {
		this.x = x_val
		this.y = y_val
	}

	// Method
	int distance_from_origin() {
		return sqrt(x*x + y*y)
	}
}

// Basic class
class Animal {
	int age

	// Constructor
	void Animal(int age) {
		this.age = age
	}

	int get_age() {
		return this.age
	}
}
