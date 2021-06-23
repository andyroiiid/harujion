return {
  version = "1.5",
  luaversion = "5.1",
  tiledversion = "1.7.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 15,
  height = 10,
  tilewidth = 16,
  tileheight = 16,
  nextlayerid = 3,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "tileset",
      firstgid = 1,
      filename = "test_tileset.tsx",
      exportfilename = "test_tileset.lua"
    }
  },
  layers = {
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 15,
      height = 10,
      id = 1,
      name = "Ground",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        18, 52, 1, 18, 52, 52, 35, 1, 35, 52, 18, 52, 1, 18, 52,
        18, 1, 18, 18, 35, 1, 35, 1, 1, 52, 18, 35, 52, 1, 52,
        52, 1, 35, 1, 35, 35, 52, 35, 18, 1, 35, 52, 35, 18, 18,
        1, 18, 52, 18, 18, 52, 35, 1, 1, 35, 52, 1, 18, 35, 18,
        52, 35, 1, 35, 52, 1, 18, 1, 52, 1, 1, 35, 105, 52, 18,
        88, 88, 88, 90, 88, 88, 87, 18, 52, 92, 92, 92, 105, 92, 92,
        35, 35, 1, 105, 18, 1, 103, 88, 88, 88, 88, 88, 107, 88, 88,
        35, 1, 1, 105, 18, 52, 52, 18, 35, 18, 52, 52, 1, 1, 35,
        35, 35, 35, 105, 35, 18, 52, 1, 1, 52, 1, 52, 1, 52, 18,
        1, 1, 52, 105, 1, 52, 1, 35, 35, 52, 1, 35, 35, 1, 52
      }
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 15,
      height = 10,
      id = 2,
      name = "Objects",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 81, 84, 0, 45, 29, 13, 65, 25, 62, 114, 98, 116, 62,
        0, 97, 115, 99, 0, 14, 45, 47, 0, 25, 62, 114, 115, 116, 62,
        0, 100, 118, 101, 0, 0, 0, 0, 0, 25, 79, 131, 132, 133, 79,
        0, 0, 0, 0, 0, 0, 0, 0, 17, 25, 108, 94, 110, 94, 109,
        0, 0, 0, 0, 0, 0, 0, 0, 17, 42, 43, 44, 0, 42, 43,
        0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
