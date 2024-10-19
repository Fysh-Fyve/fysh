// @ts-check
'use strict';

// TODO: build this in React?
// @ts-expect-error prevent re-declaration
if (typeof WebInterpreter === 'undefined') {
  const WASM_URL = 'web-interpreter-opt.wasm';
  class WebInterpreter extends HTMLElement {
    /**
     * @typedef {{
     *   getBuffer(): number
     *   goFysh(addr: number, len: number): void
     *   memory: WebAssembly.Memory
     * }} Exports
     */
    /**
     * @type {WebAssembly.Instance & { exports: WebAssembly.Exports & Exports }}
     */
    // @ts-expect-error private identifier
    #wasm;

    /**
     *
     * @param {string} text
     * @returns
     */
    // @ts-expect-error private identifier
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

    // @ts-expect-error private identifier
    #logText(addr, length) {
      const memory = this.#wasm.exports.memory;
      const bytes = memory.buffer.slice(addr, addr + length);
      const decoder = new TextDecoder('UTF-8');
      const text = decoder.decode(new Int8Array(bytes));
      return text;
    }

    // @ts-expect-error private identifier
    #newRunner() {
      // @ts-expect-error wasm_exec.js class
      const go = new Go();
      /** @type {HTMLTextAreaElement}  */
      const output = this.querySelector('textarea[data-id="output"]');
      go.importObject['main.go.printError'] = (addr, length) => {
        output.value = (output.value ?? '') + this.#logText(addr, length) + '\n';
      };
      go.importObject['main.go.printOut'] = (addr, length) => {
        output.value = (output.value ?? '') + this.#logText(addr, length) + '\n';
      };
      go.importObject.env = {
        printError: go.importObject['main.go.printError'],
        printOut: go.importObject['main.go.printOut'],
      };

      return go;
    }

    connectedCallback() {
      // @ts-expect-error
      this.querySelector('textarea[data-id="input"]').value = `><//> Calculate 5!

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
(+o ><factorial> ~ ><//> Should be 120`;
      const go = this.#newRunner();
      if ('instantiateStreaming' in WebAssembly) {
        WebAssembly.instantiateStreaming(fetch(WASM_URL), go.importObject).then((obj) => {
          // @ts-expect-error
          this.#wasm = obj.instance;
          go.run(this.#wasm);
        });
      } else {
        fetch(WASM_URL)
          .then((resp) => resp.arrayBuffer())
          .then((bytes) =>
            WebAssembly.instantiate(bytes, go.importObject).then((obj) => {
              // @ts-expect-error
              this.#wasm = obj.instance;
              go.run(this.#wasm);
            }),
          );
      }
      this.querySelector('button[data-id="play"]')?.addEventListener('click', () => {
        if (!this.#wasm) return;
        // @ts-expect-error
        this.querySelector('textarea[data-id="output"]').value = '';
        // @ts-expect-error
        const inputText = this.querySelector('textarea[data-id="input"]').value;
        const [addr, len] = this.#insertText(inputText);
        this.#wasm.exports.goFysh(addr, len);
      });
    }
  }

  if (!customElements.get('web-interpreter')) {
    customElements.define('web-interpreter', WebInterpreter);
  }
}
