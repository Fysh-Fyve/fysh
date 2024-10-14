import Head from '@docusaurus/Head';
import React, { useEffect } from 'react';

declare global {
  namespace JSX {
    interface IntrinsicElements {
      'web-interpreter': React.DetailedHTMLProps<React.HTMLAttributes<HTMLElement>, HTMLElement>;
    }
  }
}

export default function Interpreter() {
  return (
    <>
      <Head>
        <script src="/js/wasm_exec.js" async></script>
        <script src="/js/interpreter.js" async></script>
      </Head>
      <web-interpreter className="interpreter">
        <div>
          <button className="play">Swim</button>
        </div>
        <textarea className="input"></textarea>
        <textarea className="output" readOnly aria-readonly></textarea>
      </web-interpreter>
    </>
  );
}
