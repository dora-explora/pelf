use std::fs::File;
use std::env::args;
use std::io::{Error, Read, Result};

fn main() -> Result<()> {
    let args: Vec<String> = args().collect();
    let lnxpath: String;
    let winpath: String;
    let plfpath: String;
    match args.len() {
        0|1 => panic!("Too few arguments"),
        2 => { lnxpath = args[1].clone(); winpath = lnxpath.to_owned() + ".exe"; plfpath = lnxpath.to_owned() + ".elf"; }
        3 => { lnxpath = args[1].clone(); winpath = args[2].clone(); plfpath = lnxpath.to_owned() + ".elf"; }
        4 => { lnxpath = args[1].clone(); winpath = args[2].clone(); plfpath = args[3].clone(); }
        5.. => panic!("Too many arguments")
    }
    let lnxfile = File::open(lnxpath)?;
    let winfile = File::open(winpath)?;
    let mut plffile = File::create(plfpath)?;
    return Ok(())
}
