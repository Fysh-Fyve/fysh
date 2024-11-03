import React, { useCallback, useEffect, useState } from 'react';
import styles from './Interpreter.module.css';
import useFysh from './useFysh';

export default function Interpreter() {
  const [input, setInput] = useState('');
  const [output, setOutput] = useState('');

  const printOutput = useCallback(
    (text: string) => {
      setOutput((output) => output.concat(text + '\n'));
    },
    [setOutput],
  );

  const fysh = useFysh(printOutput);

  function runFysh() {
    setOutput('');
    fysh.runFysh(input);
  }

  useEffect(() => {
    let mounted = true;
    fetch('/fysh/factorial.fysh')
      .then((res) => res.text())
      .then((input) => {
        if (mounted) {
          setInput(input);
        }
      });

    return () => {
      mounted = false;
    };
  }, [setInput]);

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
