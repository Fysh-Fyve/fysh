declare class Go {
  importObject: Record<string, any> & {
    env: Record<string, any>;
  };
  run(wasm: WebAssembly.Instance): void;
}

type Exports = {
  getBuffer(): number;
  goFysh(addr: number, len: number): void;
  memory: WebAssembly.Memory;
};
type FyshWASMInstance = WebAssembly.Instance & { exports: WebAssembly.Exports & Exports };

type OutputFunc = (output: string) => void;

export default class FyshWrapper {
  private go: Go;
  private wasm: FyshWASMInstance;

  constructor(private onPrintOut: OutputFunc, private onPrintError: OutputFunc) {}

  public async initialize(): Promise<void> {
    this.go = new Go();
    this.go.importObject['main.go.printError'] = (addr: number, length: number) => {
      this.onPrintOut(this.logText(addr, length));
    };
    this.go.importObject['main.go.printOut'] = (addr: number, length: number) => {
      this.onPrintError(this.logText(addr, length));
    };
    this.go.importObject.env = {
      printError: this.go.importObject['main.go.printError'],
      printOut: this.go.importObject['main.go.printOut'],
    };
    const WASM_URL = '/web-interpreter-opt.wasm';
    const obj =
      'instantiateStreaming' in WebAssembly
        ? await WebAssembly.instantiateStreaming(fetch(WASM_URL), this.go.importObject)
        : await fetch(WASM_URL)
            .then((resp) => resp.arrayBuffer())
            .then((bytes) => WebAssembly.instantiate(bytes, this.go.importObject));
    // @ts-expect-error
    this.wasm = obj.instance;
    this.go.run(this.wasm);
  }

  public runFysh(program: string) {
    const [addr, len] = this.insertText(program);
    this.wasm.exports.goFysh(addr, len);
  }

  private insertText(text: string) {
    const encoder = new TextEncoder();
    const bytes = encoder.encode(text);

    // Get the address of the writable memory.
    const addr = this.wasm.exports.getBuffer();
    const buffer = this.wasm.exports.memory.buffer;

    const mem = new Int8Array(buffer);
    const view = mem.subarray(addr, addr + bytes.length);

    for (let i = 0; i < bytes.length; i++) {
      view[i] = bytes[i];
    }

    // Return the address we started at.
    return [addr, bytes.length];
  }

  private logText(addr: number, length: number) {
    const memory = this.wasm.exports.memory;
    const bytes = memory.buffer.slice(addr, addr + length);
    const decoder = new TextDecoder('UTF-8');
    const text = decoder.decode(new Int8Array(bytes));
    return text;
  }
}
