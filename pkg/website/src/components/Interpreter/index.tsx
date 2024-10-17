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
      {/* TODO: Make this a React component... or not.
        https://github.com/facebook/react/issues/4933 */}
      <web-interpreter {...{ class: styles.interpreter }}>
        <div className={styles.btnContainer}>
          <button className={styles.swimButton} data-id="play">
            Swim
          </button>
        </div>
        <div className={styles.boxContainer}>
          <div>
            <textarea className={styles.inputBox} data-id="input"></textarea>
          </div>
          <div>
            <textarea className={styles.outputBox} data-id="output" readOnly aria-readonly></textarea>
          </div>
        </div>
      </web-interpreter>
    </>
  );
}
