mod quadrangle_module;

use quadrangle_module::QuadrangleChecker;

fn main() {
    
}

//------------------------------------------Тест 1------------------------------------------
#[test]
fn quadrangle_checker_correct_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "true")
}

//------------------------------------------Группа 1------------------------------------------
#[test]
fn quadrangle_checker_a_0_inpt() {
    assert_eq!(QuadrangleChecker::check(0 as f64, 3 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_b_0_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 0 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_c_0_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 0 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_d_0_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 5 as f64, 0 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

//------------------------------------------Группа 2------------------------------------------
#[test]
fn quadrangle_checker_a_neg_inpt() {
    assert_eq!(QuadrangleChecker::check(-1 as f64, 3 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_b_neg_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, -1 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_c_neg_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, -1 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_d_neg_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 5 as f64, -1 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

//------------------------------------------Группа 3------------------------------------------
#[test]
fn quadrangle_checker_a_right_inpt() {
    assert_eq!(QuadrangleChecker::check(14 as f64, 3 as f64, 5 as f64, 7 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "true")
}

#[test]
fn quadrangle_checker_b_right_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 14 as f64, 5 as f64, 3 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "true")
}

#[test]
fn quadrangle_checker_c_right_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 14 as f64, 5 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "true")
}

#[test]
fn quadrangle_checker_d_right_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "true")
}

//------------------------------------------Группа 4------------------------------------------
#[test]
fn quadrangle_checker_a_big_inpt() {
    assert_eq!(QuadrangleChecker::check(17 as f64, 3 as f64, 5 as f64, 7 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_b_big_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 17 as f64, 5 as f64, 3 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_c_big_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 17 as f64, 5 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_d_big_inpt() {
    assert_eq!(QuadrangleChecker::check(7 as f64, 3 as f64, 5 as f64, 17 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

//------------------------------------------Группа 5------------------------------------------
#[test]
fn quadrangle_checker_a_equ_inpt() {
    assert_eq!(QuadrangleChecker::check(22 as f64, 3 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_b_equ_inpt() {
    assert_eq!(QuadrangleChecker::check(3 as f64, 22 as f64, 5 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_c_equ_inpt() {
    assert_eq!(QuadrangleChecker::check(5 as f64, 3 as f64, 22 as f64, 14 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

#[test]
fn quadrangle_checker_d_equ_inpt() {
    assert_eq!(QuadrangleChecker::check(14 as f64, 3 as f64, 5 as f64, 22 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "false")
}

//------------------------------------------Тест 22------------------------------------------
#[test]
fn quadrangle_checker_square() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 1 as f64, 1 as f64, 1 as f64, 90 as f64, 90 as f64, 90 as f64, 90 as f64), "square")
}

//------------------------------------------Группа 6------------------------------------------
#[test]
fn quadrangle_checker_rectangle_long() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 2 as f64, 1 as f64, 2 as f64, 90 as f64, 90 as f64, 90 as f64, 90 as f64), "rectangle")
}

#[test]
fn quadrangle_checker_rectangle_wide() {
    assert_eq!(QuadrangleChecker::check(2 as f64, 1 as f64, 2 as f64, 1 as f64, 90 as f64, 90 as f64, 90 as f64, 90 as f64), "rectangle")
}

//------------------------------------------Группа 7------------------------------------------
#[test]
fn quadrangle_checker_rhombus_long() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 1 as f64, 1 as f64, 1 as f64, 120 as f64, 120 as f64, 60 as f64, 60 as f64), "rhombus")
}

#[test]
fn quadrangle_checker_rhombus_wide() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 1 as f64, 1 as f64, 1 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "rhombus")
}

//------------------------------------------Группа 8------------------------------------------
#[test]
fn quadrangle_checker_parallelogram_long() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 2 as f64, 1 as f64, 2 as f64, 120 as f64, 120 as f64, 60 as f64, 60 as f64), "parallelogram")
}

#[test]
fn quadrangle_checker_parallelogram_wide() {
    assert_eq!(QuadrangleChecker::check(2 as f64, 1 as f64, 2 as f64, 1 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "parallelogram")
}

#[test]
fn quadrangle_checker_parallelogram_long_sec() {
    assert_eq!(QuadrangleChecker::check(1 as f64, 2 as f64, 1 as f64, 2 as f64, 60 as f64, 60 as f64, 120 as f64, 120 as f64), "parallelogram")
}

#[test]
fn quadrangle_checker_parallelogram_wide_sec() {
    assert_eq!(QuadrangleChecker::check(2 as f64, 1 as f64, 2 as f64, 1 as f64, 120 as f64, 120 as f64, 60 as f64, 60 as f64), "parallelogram")
}