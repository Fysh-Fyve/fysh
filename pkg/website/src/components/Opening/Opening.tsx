import clsx from 'clsx';
import React from 'react';
import DarkFysh from './DarkFysh';
import OGFysh from './OGFysh';
import styles from './Opening.module.css';
import Wave from './Wave';

export default function Opening() {
  return (
    <div style={{ height: '100%' }}>
      <div className={clsx('opening', styles.opening)} id="opening">
        <OGFysh />
        <Wave />
        <DarkFysh />
      </div>
    </div>
  );
}
