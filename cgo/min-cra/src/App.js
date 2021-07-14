import React from 'react';
function App() {

  function handleSubmitSayHello(e) {
    e.preventDefault()
    window.sayHelloJS("hi")
  }
  function handleSubmitTest1(e) {
    e.preventDefault()
    window.test1JS("dummy input")
  }
  return (
    <div>
      <div>
        <button type="submit" onClick={(e) => handleSubmitSayHello(e)}>call sayHello() in go</button>
        <br/>
        <button type="submit" onClick={(e) => handleSubmitTest1(e)}>call test1() in go</button>
      </div>
    </div>
  );
}
export default App;