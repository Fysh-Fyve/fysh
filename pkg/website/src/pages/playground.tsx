import React from 'react';
import Layout from '@theme/Layout';

import Interpreter from '../components/Interpreter';

export default function Playground(): JSX.Element {
  return (
    <Layout
      title="Fysh Playground"
      description="Play around with the Fysh programming language using the online WASM interpreter"
    >
      <Interpreter />
    </Layout>
  );
}
