use chrono::prelude::*;

fn main() {
    let dt1 = Utc.ymd(2022, 09, 30).and_hms(12, 1, 2);
    println!("{dt1}");
    let dt2 = "2022-09-30 12:01:02 UTC".parse::<DateTime<Utc>>().unwrap();
    assert_eq!(dt1, dt2);
}
