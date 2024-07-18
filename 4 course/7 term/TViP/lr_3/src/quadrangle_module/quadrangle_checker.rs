pub struct QuadrangleChecker {

}

impl QuadrangleChecker {
    pub fn check(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> String {
        if side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0 || side4 <= 0.0 {
            return "false".to_string();
        }

        if Self::is_square(side1, side2, side3, side4, angle1, angle2, angle3, angle4) {
            return "square".to_string();
        }
        if Self::is_rhombus(side1, side2, side3, side4, angle1, angle2, angle3, angle4) {
            return "rhombus".to_string();
        }
        if Self::is_rectangle(side1, side2, side3, side4, angle1, angle2, angle3, angle4) {
            return "rectangle".to_string();
        }
        if Self::is_parallelogram(side1, side2, side3, side4, angle1, angle2, angle3, angle4) {
            return "parallelogram".to_string();
        }
        if Self::is_quadrangle(side1, side2, side3, side4, angle1, angle2, angle3, angle4) {
            return "true".to_string();
        }

        return "false".to_string();
    }

    fn is_square(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> bool {
        if side1 == side2 && side2 == side3 
            && side3 == side4 && angle1 == 90.0 
                && angle2 == 90.0 && angle3 == 90.0 
                    && angle4 == 90.0 {
            return true;
        }
        false
    }
     
    fn is_rectangle(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> bool {
        if side1 == side3 && side2 == side4 
            && angle1 == 90.0 && angle2 == 90.0 
                && angle3 == 90.0 && angle4 == 90.0 {
            return true;
        }
        false
    }
     
    fn is_parallelogram(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> bool {
        if side1 == side3 && side2 == side4 
            && angle1 + angle3 == 180.0 && angle2 + angle4 == 180.0 {
            return true;
        }
        false
    }
     
    fn is_rhombus(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> bool {
        if side1 == side2 && side2 == side3 
            && side3 == side4 
                && angle1 + angle3 == 180.0 && angle2 + angle4 == 180.0 {
            return true;
        }
        false
    }

    fn is_quadrangle(side1: f64, side2: f64, side3: f64, side4: f64, angle1: f64, angle2: f64, angle3: f64, angle4: f64) -> bool {
        if (side1 + side2 + side3 > side4 && side1 + side2 + side4 > side3
            && side1 + side4 + side3 > side2 && side4 + side2 + side3 > side1)
                && angle1 + angle2 + angle3 + angle4 == 360.0 {
            return true;
        }
        false
    }
}