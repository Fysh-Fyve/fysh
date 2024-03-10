---@diagnostic disable: undefined-global
---
vim.lsp.start({
  name = "fyshls",
  cmd = { "./bin/fyshls" },
  root_dir = vim.fn.getcwd(),
})

vim.lsp.buf_attach_client(0, 1)
