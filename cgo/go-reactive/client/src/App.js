import React, { Component } from 'react';
import './App.css';
class App extends Component {
  constructor(props) {
    super(props)

    this.state = {
      message: '',
      mod: null,
      inst: null,
    }
  }

  async componentDidMount() {
    let { instance, module } = await WebAssembly.instantiateStreaming(fetch("main.wasm"), window.go.importObject)
    await window.go.run(instance)
    // saving to state.. tsk tsk not sure its the most optimal but i guess it works?? also, the value isnt that "big" anyway
    this.setState({
      mod: module,
      inst: instance
    })
  }

  handleChange = (e) => {
    e.preventDefault();
    this.setState({
      message: e.target.value
    })
  }

  handleSubmitSayHello = async (e) => {
    e.preventDefault()
    window.sayHelloJS(this.state.message)
  }

  handleSubmitTest1 = async (e) => {
    e.preventDefault()
    window.test1JS(this.state.message)
  }


  render() {
    return (
      <div className="App">
        <form>
          <input type="text" name="" id="userInput" onChange={(e) => this.handleChange(e)} style={{ marginTop: '100px' }} />
          <br />
          <button type="submit" onClick={(e) => this.handleSubmitSayHello(e)}>call sayHello() in go</button>
          <br />
          <button type="submit" onClick={(e) => this.handleSubmitTest1(e)}>call test1() in go</button>
        </form>
        <span id="message">
        </span>  
      </div>    
    )
  }
}

export default App;
