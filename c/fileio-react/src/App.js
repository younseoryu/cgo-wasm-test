import React, { useState, useEffect } from "react";
import createModule from "./wasm.mjs";

function App() {
  const [filename, setFilename] = useState( '' );
  const [add, setAdd] = useState();
  const [printFile, setPrintFile] = useState();
  const [writeFile, setWriteFile] = useState();
  const [getFile, setGetFile] = useState();
  const [ifFileExists, setIfFileExists] = useState();
  useEffect(
    // useEffect here is roughly equivalent to putting this in componentDidMount for a class component
    () => {
      createModule().then((Module) => {
        // need to use callback form (() => function) to ensure that `add` is set to the function
        // if you use setX(myModule.cwrap(...)) then React will try to set newX = myModule.cwrap(currentX), which is wrong
        setAdd(() => Module.cwrap("add", "number", ["number", "number"]));
       
        setWriteFile(() => Module.cwrap("writeFile", "number", ["string", "string"]));
        setPrintFile(() => Module.cwrap("printFile", "number", ["string"]));
        setGetFile(() => Module.cwrap("getFile", "string", ["string"]));
        setIfFileExists(() => Module.cwrap("ifFileExists", "number", ["string"]));
      });
    },
    []
  );
  if (!add || !printFile || !writeFile || !getFile || !ifFileExists) {
    return "Loading webassembly...";
  }


  function wasm_print() {
    if (ifFileExists(filename) === 0) {      
      console.log("specified file does not exist in MEMFS")
    } else {
      printFile(filename);
    }

  }

  function wasm_write() {
    fetch('./file-io.txt')
      .then(response => response.text())
      .then(data => {
        // Do something with your data
        writeFile(data, filename);
      });
  }

  function wasm_get() {
    if (ifFileExists(filename) === 0) {
     
      console.log("specified file does not exist in MEMFS")
    } else {
      let data = getFile(filename);
      localStorage.setItem('myMemfsData', data);
    }
  }


  return (
    <div className="App">
       <input
         type="text"
         value={filename}
         placeholder="Enter a file name"
         onChange={e => setFilename(e.target.value)}
       />
      <p>
        <strong>filename: {filename}</strong>
      </p>
      <button onClick={wasm_write}>
        Write a file in client side to MEMFS
      </button>
      <br />
      <button onClick={wasm_print}>
        In C, Print File in MEMFS 
      </button>
      <br />
      <button onClick={wasm_get}>
        In JS, Get buffer from the file in MEMFS
      </button>
      {/* <div>1 + 2 = {add(1, 2)}</div> */}
    </div>
  );
}

export default App;
