#include <flecs.h>
#include "../bgfx.hpp"
#include <bgfx/bgfx.h>
#include <embeded_shaders/vs_test.spirv.h>
#include <embeded_shaders/fs_test.spirv.h>
#include <bx/math.h>
#include "../window.hpp"

struct RenderData;
void on_bgfx_init(RenderData&);
void on_draw(flecs::iter);


struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
};

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

struct RenderData {
  bgfx::VertexBufferHandle vbh;
  bgfx::IndexBufferHandle ibh;
  bgfx::ProgramHandle program;
};

void test_stuff(flecs::world& world) {
  world.import<engine::Window>();
  world.component<RenderData>();

  world.system("InitRenderData")
    .with<engine::bgfx::BgfxContext>().singleton()
    .without<RenderData>().singleton()
    .iter([](flecs::iter it) {
      RenderData rdata;
      on_bgfx_init(rdata);
      it.world().set<RenderData>(rdata);
    });

  world.system("TESTDRAW")
    .kind(flecs::OnStore)
    .with<engine::bgfx::BgfxContext>().singleton()
    .with<RenderData>().singleton()
    .with<engine::window::MainWindow>().singleton()
    .iter(on_draw);
}

void on_bgfx_init(RenderData& rdata) {
  bgfx::VertexLayout layout;
  layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
		.end();
  
  rdata.vbh = bgfx::createVertexBuffer(
    bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
    layout
  );

  rdata.ibh =  bgfx::createIndexBuffer(
    bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
  );

  {
    bgfx::ShaderHandle vsh = bgfx::createShader( bgfx::makeRef(vs_test_spirv, sizeof(vs_test_spirv)) );
    assert(bgfx::isValid(vsh));

    bgfx::ShaderHandle fsh = bgfx::createShader( bgfx::makeRef(fs_test_spirv, sizeof(fs_test_spirv)) );
    assert(bgfx::isValid(fsh));

    rdata.program = bgfx::createProgram(vsh, fsh, true);
    assert(bgfx::isValid(rdata.program));
  }

}

void on_draw(flecs::iter it) {
  flecs::world world = it.world();
  const auto* p_main_window = world.get<engine::window::MainWindow>();
  const auto* p_render_data = world.get<RenderData>();

  bgfx::dbgTextPrintf(1, 1, 0x0f, "Hellow World 2");

  //set view
  {
    const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

    float view[16];
    bx::mtxLookAt(view, eye, at);

    float proj[16];
    bx::mtxProj(
      proj,
      60.0f,
      float(p_main_window->width) / float(p_main_window->height),
      0.1f,
      100.0f,
      bgfx::getCaps()->homogeneousDepth
    );

    bgfx::setViewTransform(0, view, proj);
    //bgfx::setViewRect(0, 0, 0, uint16_t(p_main_window->width), uint16_t(p_main_window->height));
  }

  float time = 0;
  float mtx[16];
  float xx = 1.0f;
  float yy = 1.0f;
	bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
	mtx[12] = -15.0f + float(xx)*3.0f;
	mtx[13] = -15.0f + float(yy)*3.0f;
	mtx[14] = 0.0f;

  bgfx::setTransform(mtx);
  bgfx::setVertexBuffer(0, p_render_data->vbh);
  bgfx::setIndexBuffer(p_render_data->ibh);

  bgfx::setState(0
    | BGFX_STATE_WRITE_R
    | BGFX_STATE_WRITE_G 
    | BGFX_STATE_WRITE_B 
    | BGFX_STATE_WRITE_A
    | BGFX_STATE_WRITE_Z
    | BGFX_STATE_DEPTH_TEST_LESS
    | BGFX_STATE_CULL_CW
    | BGFX_STATE_MSAA
    | BGFX_STATE_PT_TRISTRIP
  );

  //SPDLOG_INFO("HI DUDDLES");

  bgfx::submit(0, p_render_data->program);
}
