import Head from '@docusaurus/Head';
import React from 'react';
import styles from './styles.module.css';

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
      <web-interpreter className={styles.interpreter}>
        <div>
          <button data-id="play">Swim</button>
        </div>
        <textarea data-id="input"></textarea>
        <textarea data-id="output" readOnly aria-readonly></textarea>
      </web-interpreter>
    </>
  );
}
