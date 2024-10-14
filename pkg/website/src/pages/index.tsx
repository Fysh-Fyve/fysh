import React from 'react';
import Layout from '@theme/Layout';

import Opening from '../components/Opening';
import styles from '../components/Opening/opening.module.css';

export default function Home(): JSX.Element {
  return (
    <Layout wrapperClassName={styles.opening} title={`Hello from Fysh`} description="Description will go into a meta tag in <head />">
      <Opening />
    </Layout>
  );
}
