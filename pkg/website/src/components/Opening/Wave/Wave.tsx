import React from 'react';
import styles from './wave.module.css';

export default function Wave() {
  return (
    <>
      <div className={styles.waveContainer}>
        <div className={styles.ocean}>
          <div className={styles.wave}></div>
          <div className={styles.wave}></div>
        </div>
      </div>
    </>
  );
}
