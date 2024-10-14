import React from 'react';
import './opening/cursor.css';
import './opening/opening.css';
import styles from './styles.module.css';
import waveStyles from './wave.module.css';

export default function Opening() {
  return (
    <div
      style={{
        height: '100%',
      }}
    >
      <div className="opening" id="opening">
        <OGFysh />
        <Wave />
        <div className="bottom-fysh">
          <span className="fysh-container">
            <code className="fysh">
              &gt;&lt;<code className="c c-1">f</code>
              <code className="c c-2">y</code>
              <code className="c c-3">s</code>
              <code className="c c-4">h</code>
              <code className="blinking">&#x25AF;</code>&gt;
              <code className="blinking-after">&#x25AF;</code>
            </code>
          </span>
        </div>
      </div>
    </div>
  );
}

function OGFysh() {
  return (
    <div className={styles.ogFysh}>
      <code>&gt;&lt;&gt;</code>
    </div>
  );
}

function Wave() {
  return (
    <>
      <div className={waveStyles.waveContainer}>
        <div className={waveStyles.ocean}>
          <div className={waveStyles.wave}></div>
          <div className={waveStyles.wave}></div>
        </div>
      </div>
    </>
  );
}
