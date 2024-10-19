import useIsBrowser from '@docusaurus/useIsBrowser';
import React, { useCallback, useEffect, useState } from 'react';
import { exampleFactorial } from './factorial';
import FyshWrapper from './FyshWrapper';
import styles from './Interpreter.module.css';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';

function useScript(script: string) {
  const [loaded, setLoaded] = useState(false);
  useEffect(() => {
    const scriptTag = document.createElement('script');
    scriptTag.src = script;
    scriptTag.addEventListener('load', () => {
      setLoaded(true);
      document.head.removeChild(scriptTag);
    });
    document.head.appendChild(scriptTag);
  }, [setLoaded]);
  return loaded;
}

export default function Interpreter() {
  const context = useDocusaurusContext();
  const [input, setInput] = useState(exampleFactorial);
  const [output, setOutput] = useState('');
  const isBrowser = useIsBrowser();
  const loadedWasm = useScript('/js/wasm_exec.js');
  const printOutput = useCallback(
    (text: string) => {
      setOutput((output) => output.concat(text + '\n'));
    },
    [setOutput]
  );
  const [fysh, setFysh] = useState<FyshWrapper | null>(() => null);

  useEffect(() => {
    let mounted = true;
    if (isBrowser && loadedWasm) {
      const fysh = new FyshWrapper(printOutput, printOutput);
      fysh.initialize(context.siteConfig.baseUrl).then(() => {
        if (mounted) {
          setFysh(fysh);
        }
      });
    }
    return () => {
      mounted = false;
    };
  }, [isBrowser, loadedWasm, context.siteConfig.baseUrl]);

  function runFysh() {
    setOutput('');
    fysh.runFysh(input);
  }
  return (
    <>
      <div className={styles.interpreter}>
        <div className={styles.btnContainer}>
          <button className={styles.swimButton} disabled={fysh === null} onClick={runFysh}>
            Swim
          </button>
        </div>
        <div className={styles.boxContainer}>
          <div>
            <textarea
              className={styles.inputBox}
              value={input}
              onChange={(e) => setInput(e.target.value)}
            ></textarea>
          </div>
          <div>
            <textarea className={styles.outputBox} value={output} readOnly aria-readonly></textarea>
          </div>
        </div>
      </div>
    </>
  );
}
