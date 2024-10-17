import React from 'react';
import './opening/opening.css';
import styles from './styles.module.css';
import waveStyles from './wave.module.css';
import cursorStyles from './cursor.module.css';

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
        <DarkFysh />
      </div>
    </div>
  );
}

function DarkFysh() {
  return (
    <div className="bottom-fysh">
      <span className="fysh-container">
        <code className="fysh">
          &gt;&lt;<code className="c c-1">f</code>
          <code className="c c-2">y</code>
          <code className="c c-3">s</code>
          <code className="c c-4">h</code>
          <code className={cursorStyles.blinking}>&#x25AF;</code>&gt;
          <code className={cursorStyles.blinkingAfter}>&#x25AF;</code>
        </code>
      </span>
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
