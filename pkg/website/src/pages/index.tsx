import React from 'react';
import Layout from '@theme/Layout';

import Opening from '../components/Opening';

export default function Home(): JSX.Element {
  return (
    <Layout
      wrapperClassName='home-layout'
      title={`Hello from Fysh`}
      description="Description will go into a meta tag in <head />"
    >
      <Opening />
    </Layout>
  );
}
