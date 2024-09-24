// @ts-check
"use strict";

const WASM_URL = "web-interpreter-opt.wasm";

class WebInterpreter extends HTMLElement {
  /**
   * @type {WebAssembly.WebAssemblyInstantiatedSource['instance']}
   */
  #wasm;

  /**
   *
   * @param {string} text
   * @returns
   */
  #insertText(text) {
    const encoder = new TextEncoder();
    const bytes = encoder.encode(text);

    // Get the address of the writable memory.
    const addr = this.#wasm.exports.getBuffer();
    const buffer = this.#wasm.exports.memory.buffer;

    const mem = new Int8Array(buffer);
    const view = mem.subarray(addr, addr + bytes.length);

    for (let i = 0; i < bytes.length; i++) {
      view[i] = bytes[i];
    }

    // Return the address we started at.
    return [addr, bytes.length];
  }

  #logText(addr, length) {
    const memory = this.#wasm.exports.memory;
    const bytes = memory.buffer.slice(addr, addr + length);
    const decoder = new TextDecoder("UTF-8");
    const text = decoder.decode(new Int8Array(bytes));
    return text;
  }

  #newRunner() {
    const go = new Go();
    go.importObject["main.go.printError"] = (addr, length) => {
      console.error(this.#logText(addr, length));
    };
    go.importObject["main.go.printOut"] = (addr, length) => {
      console.log(this.#logText(addr, length));
    };
    go.importObject.env = {
      printError: go.importObject["main.go.printError"],
      printOut: go.importObject["main.go.printOut"],
    };

    return go;
  }

  connectedCallback() {
    this.querySelector("textarea.input").value = `><//> Calculate 5!

><number>    ≈ ><{({°> ~  ><//> b101 = 5
><factorial> ≈ ><(({°> ~  ><//> b001 = 1

><//> while number > 1
><(((@> [><number> o~ ><(({°>]
><>
	><//> factorial = factorial * number
	><factorial> ≈ ><factorial> ♡ ><number> ~

	><//> number -= 1
	<number><< ~
<><
(+o ><factorial> ~ ><//> Should be 120
`
    const go = this.#newRunner();
    if ("instantiateStreaming" in WebAssembly) {
      WebAssembly.instantiateStreaming(fetch(WASM_URL), go.importObject).then(
        (obj) => {
          this.#wasm = obj.instance;
          go.run(this.#wasm);
        }
      );
    } else {
      fetch(WASM_URL)
        .then((resp) => resp.arrayBuffer())
        .then((bytes) =>
          WebAssembly.instantiate(bytes, go.importObject).then((obj) => {
            this.#wasm = obj.instance;
            go.run(this.#wasm);
          })
        );
    }
    this.querySelector("button.play")?.addEventListener("click", () => {
      if (!this.#wasm) return;
      // @ts-expect-error
      const inputText = this.querySelector("textarea.input").value;
      const [addr, len] = this.#insertText(inputText);
      this.#wasm.exports.goFysh(addr, len);
    });
  }
}

customElements.define("web-interpreter", WebInterpreter);