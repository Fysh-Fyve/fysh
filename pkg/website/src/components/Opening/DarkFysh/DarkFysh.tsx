import React from 'react';
import styles from './DarkFysh.module.css';
import clsx from 'clsx';

export default function DarkFysh() {
  return (
    <div className={styles.bottomFysh}>
      <span className={styles.fyshContainer}>
        <code className={styles.fysh}>
          &gt;&lt;<code className={clsx(styles.c, styles.c1)}>f</code>
          <code className={clsx(styles.c, styles.c2)}>y</code>
          <code className={clsx(styles.c, styles.c3)}>s</code>
          <code className={clsx(styles.c, styles.c4)}>h</code>
          <code className={clsx(styles.c, styles.c5)}>-</code>
          <code className={clsx(styles.c, styles.c6)}>f</code>
          <code className={clsx(styles.c, styles.c7)}>y</code>
          <code className={clsx(styles.c, styles.c8)}>v</code>
          <code className={clsx(styles.c, styles.c9)}>e</code>
          <code className={styles.blinking}>&#x25AF;</code>&gt;
          <code className={styles.blinkingAfter}>&#x25AF;</code>
        </code>
      </span>
    </div>
  );
}
