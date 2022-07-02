use std::io::{Result as IoResult, Write};
// use std::net::TcpStream;

use super::StatusCode;

pub struct Response {
    status_code: StatusCode,
    body: Option<String>,
}

impl Response {
    pub fn new(status_code: StatusCode, body: Option<String>) -> Self {
        Response { status_code, body }
    }

    // * dynamic dispatch
    // pub fn send(&self, stream: &mut dyn Write) -> IoResult<()> {

    // * static dispach:
    // - pros: no vtable, no runtime cost, so it runs faster
    // -cons: bigger binary, more memory used, slower compilation
    // creates a new function with the concrete type depending on the caller.
    // 1) called with a TcpStream:
    //    pub fn send_TcpStrem(&self, stream: &mut TcpStream) -> IoResult<()> ;
    // 2) called with a File:
    //    pub fn send_File(&self, stream: &mut File) -> IoResult<()> ;
    pub fn send(&self, stream: &mut impl Write) -> IoResult<()> {
        let body = match &self.body {
            Some(b) => b,
            None => "",
        };
        write!(
            stream,
            "HTTP/1.1 {} {}\r\n\r\n{}",
            self.status_code,
            self.status_code.reason_phrase(),
            body
        )
    }
}
