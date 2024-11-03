import useIsBrowser from '@docusaurus/useIsBrowser';
import { useEffect, useState } from 'react';
import FyshWrapper from './FyshWrapper';
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

export default function useFysh(printOutput: (text: string) => void) {
  const context = useDocusaurusContext();
  const isBrowser = useIsBrowser();
  const loadedWasm = useScript('/js/wasm_exec.js');
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

  return fysh;
}
