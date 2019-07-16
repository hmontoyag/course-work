// Define class Teacher, subclass of AcademicPerson
public class Teacher extends AcademicPerson {
	// Instance variables
	private static final int MAX_COURSES = 10; // maximum courses

	// Constructor
	public Teacher(String name, String address) {
		super(name, address);
		courses = new String[MAX_COURSES];
	}

	
	// It adds a course into the list of courses.
	// This method throws ArrayElementException when the course that is being
	// added to the list already exists in it.
	public void addCourse(String course) throws ArrayElementException {
        int e=0;
		for (int i = 0; i < numCourses; i++) {
			if (courses[i].equalsIgnoreCase(course)) {
                e++;
				throw new ArrayElementException("Course Already in list!");
			}
		}
        if (e==0) {
            courses[numCourses] = course;
            numCourses++;
        }


	}

	// It removes a course into the list of courses.
	// This method throws ArrayElementException when the course does not exist
	// in the list.
	public void removeCourse(String course) throws ArrayElementException {
        int e = 0;
		for (int i = 0; i < numCourses; i++) {
			if (courses[i] .equalsIgnoreCase(course)) {
                e++;
				for (int j = i; j < MAX_COURSES; j++) {
                    if ( j == MAX_COURSES - 1) {
                        courses[j] = null;
                    } else {
                        courses[j] = courses[j + 1];
                    }
                }
                numCourses--;

			}
		}
        if ( e == 0 ) {
            throw new ArrayElementException("Course not found!");
        }


	}

	// It prints all the courses in the list in each line
	@Override
	public void printCourses() {
        System.out.println("Courses teaching this semester:");
        for (int i = 0; i < numCourses; i ++) {
            System.out.println( courses[i] );
        }

	}

	@Override
	public String toString() {
		return "Teacher: " + super.toString();
	}

}