---@diagnostic disable: undefined-global
local client = vim.lsp.start({
  name = "fyshls",
  cmd = { "./bin/fyshls" },
  root_dir = vim.fn.getcwd(),
})
if not client then
  vim.notify("failed to start fysh")
  return
end

vim.lsp.buf_attach_client(client, 1)
