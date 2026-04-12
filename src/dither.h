#pragma once
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

/* 4x4 Bayer matrix - first 16 bytes of kernel's dither_bayer_04 */
static const uint8_t dither_bayer_04[] = {
	7, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5,
};

/* https://momentsingraphics.de/BlueNoise.html : 16_16/LDR_LLL1_0.png >> 4 */
static const uint8_t dither_blue_noise_16[] = {
	6,	3,	8,	10, 7,	12, 4,	11, 12, 3,	9,	5,	4,	2,	5,	15, 1,	6,	14,
	13, 2,	15, 9,	1,	2,	6,	13, 10, 12, 8,	0,	10, 7,	11, 4,	0,	4,	10,
	7,	5,	13, 8,	15, 1,	7,	3,	14, 13, 2,	12, 9,	8,	11, 6,	3,	14, 10,
	3,	0,	11, 4,	15, 9,	4,	0,	15, 3,	5,	14, 0,	12, 1,	11, 6,	9,	12,
	2,	5,	11, 6,	13, 10, 7,	2,	13, 9,	8,	4,	15, 5,	14, 3,	7,	9,	1,
	8,	5,	12, 1,	15, 4,	2,	11, 7,	0,	2,	10, 6,	15, 11, 13, 3,	6,	11,
	9,	7,	10, 6,	14, 8,	13, 9,	12, 0,	4,	1,	14, 2,	14, 1,	4,	0,	12,
	3,	1,	12, 5,	3,	7,	13, 8,	5,	7,	9,	13, 8,	15, 10, 14, 6,	2,	15,
	10, 1,	14, 11, 3,	12, 10, 0,	6,	11, 3,	5,	8,	11, 9,	4,	2,	8,	6,
	9,	2,	15, 5,	3,	1,	4,	13, 2,	0,	4,	14, 7,	12, 15, 0,	4,	7,	1,
	14, 8,	15, 10, 7,	12, 15, 6,	9,	0,	13, 10, 6,	13, 12, 5,	12, 10, 1,
	5,	9,	1,	10, 11, 3,	1,	5,	4,	2,	8,	10, 3,	7,	2,	13, 14, 3,	8,
	5,	14, 13, 7,	9,	15, 11, 1,	15, 6,	0,	8,	4,	11, 0,	13, 2,	6,	0,
	8,	14, 5,	0,	7,	14, 12, 9,	11,
};

/* https://momentsingraphics.de/BlueNoise.html : 32_32/LDR_LLL1_0.png >> 4 */
static const uint8_t dither_blue_noise_32[] = {
	9,	10, 13, 15, 9,	12, 13, 14, 8,	15, 2,	3,	15, 9,	6,	0,	15, 7,	3,
	5,	4,	11, 14, 3,	7,	1,	4,	6,	9,	12, 5,	4,	15, 5,	3,	11, 7,	4,
	1,	6,	4,	10, 13, 7,	5,	2,	13, 4,	8,	10, 1,	14, 2,	13, 7,	2,	15,
	9,	11, 5,	0,	13, 1,	7,	2,	6,	1,	2,	14, 0,	10, 8,	11, 5,	0,	10,
	8,	14, 11, 2,	11, 14, 12, 9,	7,	1,	10, 8,	5,	12, 2,	13, 14, 8,	3,
	11, 9,	14, 13, 8,	6,	9,	13, 2,	15, 1,	9,	14, 1,	4,	10, 6,	5,	0,
	6,	4,	15, 11, 5,	0,	13, 3,	7,	10, 7,	2,	10, 14, 1,	11, 5,	4,	12,
	15, 5,	3,	7,	6,	12, 3,	6,	12, 1,	7,	13, 3,	8,	12, 0,	3,	14, 11,
	6,	4,	15, 1,	4,	12, 5,	6,	8,	0,	10, 7,	1,	11, 0,	9,	10, 14, 4,
	11, 8,	15, 3,	14, 9,	15, 11, 2,	9,	6,	13, 9,	1,	10, 6,	12, 9,	0,
	15, 3,	4,	15, 9,	14, 3,	7,	4,	14, 13, 0,	8,	2,	5,	0,	10, 7,	2,
	1,	5,	7,	13, 4,	7,	2,	11, 8,	14, 2,	8,	11, 13, 9,	12, 5,	2,	13,
	6,	10, 12, 1,	6,	2,	10, 14, 12, 9,	4,	12, 6,	10, 14, 10, 8,	0,	15,
	1,	14, 4,	0,	13, 3,	6,	2,	7,	14, 3,	11, 0,	8,	15, 3,	8,	11, 5,
	15, 3,	7,	1,	13, 15, 0,	4,	13, 1,	3,	12, 10, 9,	5,	3,	11, 7,	15,
	5,	12, 1,	10, 6,	8,	5,	1,	12, 5,	2,	10, 9,	1,	13, 11, 5,	3,	8,
	11, 8,	7,	5,	15, 6,	4,	13, 7,	15, 9,	6,	0,	10, 3,	8,	13, 1,	13,
	14, 10, 2,	7,	14, 13, 7,	6,	8,	0,	12, 9,	2,	6,	12, 2,	9,	11, 2,
	8,	0,	12, 1,	10, 2,	8,	14, 15, 4,	2,	6,	9,	4,	7,	12, 9,	0,	4,
	3,	12, 2,	15, 4,	7,	10, 15, 0,	14, 5,	0,	14, 11, 5,	8,	3,	13, 12,
	4,	11, 5,	0,	12, 15, 11, 3,	1,	15, 5,	9,	13, 1,	14, 10, 6,	9,	14,
	1,	4,	3,	10, 13, 8,	6,	12, 3,	15, 6,	4,	9,	1,	6,	9,	7,	4,	9,
	0,	5,	8,	13, 2,	6,	11, 7,	4,	11, 0,	3,	13, 5,	12, 7,	8,	1,	4,
	2,	9,	14, 1,	10, 7,	11, 15, 3,	13, 10, 1,	7,	14, 12, 6,	10, 3,	12,
	14, 2,	8,	5,	12, 8,	2,	11, 8,	3,	11, 15, 12, 7,	0,	5,	11, 8,	0,
	14, 2,	5,	0,	14, 6,	4,	10, 2,	15, 1,	8,	5,	0,	10, 15, 4,	1,	15,
	10, 0,	14, 13, 0,	5,	6,	11, 15, 9,	4,	2,	12, 5,	11, 9,	8,	12, 11,
	3,	13, 7,	4,	11, 13, 9,	7,	3,	13, 6,	14, 7,	5,	4,	6,	9,	2,	10,
	13, 3,	1,	6,	13, 14, 9,	3,	7,	4,	15, 2,	8,	1,	15, 9,	2,	6,	0,
	15, 4,	11, 1,	11, 9,	3,	11, 15, 7,	3,	14, 7,	8,	4,	12, 8,	5,	0,
	8,	15, 1,	13, 6,	9,	13, 11, 5,	0,	14, 10, 8,	3,	12, 6,	8,	4,	0,
	12, 1,	10, 0,	12, 5,	11, 1,	15, 13, 2,	10, 3,	6,	11, 1,	12, 3,	0,
	4,	6,	8,	11, 6,	4,	12, 1,	10, 14, 2,	15, 10, 5,	8,	13, 2,	9,	14,
	0,	4,	9,	5,	7,	11, 14, 4,	12, 7,	10, 5,	14, 10, 1,	12, 3,	13, 2,
	14, 7,	5,	0,	7,	12, 3,	14, 4,	6,	4,	10, 3,	13, 10, 2,	6,	0,	15,
	1,	9,	2,	5,	14, 9,	7,	2,	15, 7,	1,	10, 8,	0,	11, 9,	13, 4,	7,
	11, 0,	9,	12, 15, 1,	6,	7,	8,	14, 12, 10, 3,	7,	8,	15, 0,	3,	1,
	13, 4,	5,	9,	14, 4,	6,	15, 3,	2,	15, 10, 1,	5,	15, 7,	1,	13, 8,
	11, 15, 2,	1,	4,	13, 5,	11, 13, 4,	10, 12, 8,	11, 14, 12, 0,	3,	10,
	13, 5,	9,	11, 1,	6,	13, 8,	2,	11, 3,	5,	4,	0,	9,	5,	11, 7,	9,
	2,	0,	12, 6,	2,	15, 6,	0,	8,	10, 13, 7,	11, 2,	0,	12, 6,	8,	14,
	9,	3,	14, 6,	9,	14, 12, 14, 3,	10, 13, 3,	6,	15, 8,	3,	10, 7,	5,
	9,	3,	6,	2,	4,	8,	5,	15, 7,	10, 2,	4,	3,	11, 1,	12, 4,	8,	2,
	7,	9,	6,	1,	7,	14, 10, 12, 5,	14, 0,	13, 13, 1,	14, 4,	12, 15, 1,
	9,	14, 3,	8,	13, 15, 0,	5,	7,	15, 0,	12, 10, 2,	0,	11, 13, 4,	0,
	1,	3,	7,	9,	11, 4,	2,	8,	11, 14, 7,	10, 0,	6,	11, 4,	0,	6,	12,
	10, 9,	13, 10, 6,	3,	15, 5,	14, 7,	15, 9,	8,	11, 13, 2,	15, 1,	6,
	7,	12, 0,	2,	9,	3,	12, 5,	2,	12, 14, 9,	7,	1,	4,	2,	5,	1,	9,
	13, 6,	10, 4,	3,	5,	7,	14, 5,	6,	10, 8,	12, 15, 10, 5,	13, 5,	15,
	8,	14, 7,	8,	1,	5,	3,	14, 13, 8,	15, 11, 7,	1,	8,	0,	12, 2,	12,
	1,	13, 3,	1,	12, 0,	4,	3,	1,	8,	11, 1,	4,	11, 0,	10, 15, 11, 9,
	12, 7,	0,	10, 6,	3,	14, 4,	11, 14, 6,	8,	15, 4,	9,	10, 8,	5,	14,
	7,	9,	13, 6,	12, 0,	8,	6,	2,	3,	5,	2,	0,	6,	11, 4,	12, 1,	9,
	12, 5,	2,	13, 9,	0,	10, 6,	0,	11, 13, 15, 2,	10, 2,	15, 3,
};

static const char *DITHER_VERT = R"(#version 100
attribute vec2 pos;
attribute vec2 uv;
uniform vec2 u_size;
varying vec2 v_uv;
varying highp vec2 v_pos;
void main() {
  v_uv = uv;
  v_pos = (pos * 0.5 + 0.5) * u_size;
  gl_Position = vec4(pos, 0.0, 1.0);
})";

static const char *DITHER_FRAG = R"(#version 100
precision mediump float;
uniform sampler2D u_tex;
uniform sampler2D u_noise;
uniform float u_levels;
uniform vec2 u_noise_size;
varying vec2 v_uv;
varying highp vec2 v_pos;
void main() {
  vec4 color = texture2D(u_tex, v_uv);
  vec2 noise_uv = mod(v_pos, u_noise_size) / u_noise_size;
  float threshold = texture2D(u_noise, noise_uv).r;
  vec3 scaled = color.rgb * (u_levels - 1.0);
  vec3 lo = floor(scaled);
  vec3 raw_frac = scaled - lo;
  float eps = 0.5 / 255.0;
  vec3 dither = step(eps, raw_frac) * step(raw_frac, vec3(1.0 - eps)) * step(threshold, raw_frac);
  vec3 dithered = (lo + dither) / (u_levels - 1.0);
  gl_FragColor = vec4(clamp(dithered, 0.0, 1.0), color.a);
})";

static struct {
	GLuint prog;
	GLuint noise_tex;
	GLint u_tex;
	GLint u_noise;
	GLint u_levels;
	GLint u_size;
	GLint u_noise_size;
	GLint a_pos;
	GLint a_uv;
	int noise_size;
	int current_mode;
	bool ready;
	bool tried;
} dither_gl = {.current_mode = -1};

static GLuint dither_compile_shader(GLenum type, const char *src) {
	GLuint s = glCreateShader(type);
	if (!s) {
		wlr_log(WLR_ERROR, "glCreateShader returned 0 (GL error 0x%x)",
				glGetError());
		return 0;
	}
	glShaderSource(s, 1, &src, NULL);
	glCompileShader(s);
	GLint ok;
	glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char buf[512];
		glGetShaderInfoLog(s, sizeof(buf), NULL, buf);
		wlr_log(WLR_ERROR, "shader compile error: %s", buf);
		glDeleteShader(s);
		return 0;
	}
	return s;
}

static GLuint dither_link_program(GLuint vert, GLuint frag) {
	GLuint p = glCreateProgram();
	glAttachShader(p, vert);
	glAttachShader(p, frag);
	glLinkProgram(p);
	GLint ok;
	glGetProgramiv(p, GL_LINK_STATUS, &ok);
	if (!ok) {
		char buf[512];
		glGetProgramInfoLog(p, sizeof(buf), NULL, buf);
		wlr_log(WLR_ERROR, "program link error: %s", buf);
		glDeleteProgram(p);
		return 0;
	}
	return p;
}

static void dither_upload_noise(const uint8_t *data, int size) {
	uint8_t buf[32 * 32]; /* large enough for all modes */
	for (int i = 0; i < size * size; i++)
		buf[i] = data[i] * 17; /* 0-15 -> 0-255 */
	if (dither_gl.noise_tex)
		glDeleteTextures(1, &dither_gl.noise_tex);
	glGenTextures(1, &dither_gl.noise_tex);
	glBindTexture(GL_TEXTURE_2D, dither_gl.noise_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, size, size, 0, GL_LUMINANCE,
				 GL_UNSIGNED_BYTE, buf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	dither_gl.noise_size = size;
	wlr_log(WLR_DEBUG, "uploaded %dx%d noise tex", size, size);
}

static void dither_set_mode(int mode) {
	switch (mode) {
	case 0:
		dither_upload_noise(dither_bayer_04, 4);
		break;
	case 1:
		dither_upload_noise(dither_blue_noise_16, 16);
		break;
	case 2:
		dither_upload_noise(dither_blue_noise_32, 32);
		break;
	default:
		dither_upload_noise(dither_bayer_04, 4);
		break;
	}
	dither_gl.current_mode = mode;
}

static bool dither_ensure_init(void) {
	if (dither_gl.ready)
		return true;
	if (dither_gl.tried)
		return false;
	dither_gl.tried = true;

	wlr_log(WLR_INFO, "compiling shaders");
	GLenum err = glGetError();
	(void)err;

	GLuint vert = dither_compile_shader(GL_VERTEX_SHADER, DITHER_VERT);
	GLuint frag = dither_compile_shader(GL_FRAGMENT_SHADER, DITHER_FRAG);
	if (!vert || !frag) {
		glDeleteShader(vert);
		glDeleteShader(frag);
		return false;
	}

	dither_gl.prog = dither_link_program(vert, frag);
	glDeleteShader(vert);
	glDeleteShader(frag);
	if (!dither_gl.prog)
		return false;

	dither_gl.u_tex = glGetUniformLocation(dither_gl.prog, "u_tex");
	dither_gl.u_noise = glGetUniformLocation(dither_gl.prog, "u_noise");
	dither_gl.u_levels = glGetUniformLocation(dither_gl.prog, "u_levels");
	dither_gl.u_size = glGetUniformLocation(dither_gl.prog, "u_size");
	dither_gl.u_noise_size =
		glGetUniformLocation(dither_gl.prog, "u_noise_size");
	dither_gl.a_pos = glGetAttribLocation(dither_gl.prog, "pos");
	dither_gl.a_uv = glGetAttribLocation(dither_gl.prog, "uv");

	dither_gl.ready = true;
	wlr_log(WLR_INFO, "ready");

	dither_set_mode(config.dither_mode);
	return true;
}

static void dither_finish(void) {
	if (dither_gl.noise_tex)
		glDeleteTextures(1, &dither_gl.noise_tex);
	if (dither_gl.prog)
		glDeleteProgram(dither_gl.prog);
	dither_gl = (typeof(dither_gl)){.current_mode = -1};
}

struct wlr_buffer *render_dithered(Monitor *m, bool return_buffer,
								   bool always_render) {
	struct wlr_output *output = m->wlr_output;
	int32_t width = output->width;
	int32_t height = output->height;

	if (!always_render && !wlr_scene_output_needs_frame(m->scene_output)) {
		return NULL;
	}

	struct wlr_output_state state = {0};
	wlr_output_state_init(&state);

	if (!wlr_scene_output_build_state(m->scene_output, &state, NULL)) {
		wlr_log(WLR_ERROR, "build_state failed");
		goto fallback;
	}

	if (!state.buffer)
		goto fallback;

	struct wlr_buffer *src_buf = state.buffer;
	wlr_buffer_lock(src_buf);

	if (!m->dither_swapchain || m->dither_swapchain->width != width ||
		m->dither_swapchain->height != height) {
		if (m->dither_swapchain)
			wlr_swapchain_destroy(m->dither_swapchain);
		if (!output->swapchain)
			goto fallback_src_locked;
		m->dither_swapchain = wlr_swapchain_create(
			output->allocator, width, height, &output->swapchain->format);
		if (!m->dither_swapchain)
			goto fallback_src_locked;
	}

	struct wlr_buffer *dither_buf = wlr_swapchain_acquire(m->dither_swapchain);
	if (!dither_buf)
		goto fallback_src_locked;

	struct wlr_render_pass *src_pass =
		wlr_renderer_begin_buffer_pass(drw, src_buf, NULL);
	if (!src_pass) {
		wlr_buffer_unlock(dither_buf);
		goto fallback_src_locked;
	}

	if (!dither_ensure_init()) {
		wlr_render_pass_submit(src_pass);
		wlr_buffer_unlock(dither_buf);
		goto fallback_src_locked;
	}

	if (config.dither_mode != dither_gl.current_mode)
		dither_set_mode(config.dither_mode);

	if (!m->dither_scratch_tex || m->dither_scratch_w != width ||
		m->dither_scratch_h != height) {
		if (m->dither_scratch_tex)
			glDeleteTextures(1, &m->dither_scratch_tex);
		glGenTextures(1, &m->dither_scratch_tex);
		glBindTexture(GL_TEXTURE_2D, m->dither_scratch_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
					 GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		m->dither_scratch_w = width;
		m->dither_scratch_h = height;
	}

	glBindTexture(GL_TEXTURE_2D, m->dither_scratch_tex);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);
	glBindTexture(GL_TEXTURE_2D, 0);

	wlr_render_pass_submit(src_pass);

	GLenum copy_err = glGetError();
	if (copy_err != GL_NO_ERROR) {
		wlr_log(WLR_ERROR, "copy error: 0x%x", copy_err);
		wlr_buffer_unlock(dither_buf);
		goto fallback_src_locked;
	}

	struct wlr_render_pass *dpass =
		wlr_renderer_begin_buffer_pass(drw, dither_buf, NULL);
	if (!dpass) {
		wlr_buffer_unlock(dither_buf);
		goto fallback_src_locked;
	}

	static const GLfloat quad_verts[] = {
		-1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f, 1.0f,	-1.0f, 1.0f, 0.0f,
	};

	glDisable(GL_BLEND);
	glDisable(GL_SCISSOR_TEST);
	glUseProgram(dither_gl.prog);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m->dither_scratch_tex);
	glUniform1i(dither_gl.u_tex, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dither_gl.noise_tex);
	glUniform1i(dither_gl.u_noise, 1);

	glUniform1f(dither_gl.u_levels, 16.0f);
	glUniform2f(dither_gl.u_size, (float)width, (float)height);
	glUniform2f(dither_gl.u_noise_size, (float)dither_gl.noise_size,
				(float)dither_gl.noise_size);

	glVertexAttribPointer(dither_gl.a_pos, 2, GL_FLOAT, GL_FALSE,
						  4 * sizeof(GLfloat), quad_verts);
	glVertexAttribPointer(dither_gl.a_uv, 2, GL_FLOAT, GL_FALSE,
						  4 * sizeof(GLfloat), quad_verts + 2);
	glEnableVertexAttribArray(dither_gl.a_pos);
	glEnableVertexAttribArray(dither_gl.a_uv);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(dither_gl.a_pos);
	glDisableVertexAttribArray(dither_gl.a_uv);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	wlr_render_pass_submit(dpass);
	wlr_buffer_unlock(src_buf);

	if (return_buffer) {
		wlr_output_state_finish(&state);
		return dither_buf;
	}

	wlr_output_state_set_buffer(&state, dither_buf);
	wlr_buffer_unlock(dither_buf);
	wlr_output_commit_state(output, &state);
	wlr_output_state_finish(&state);
	return NULL;

fallback_src_locked:
	wlr_buffer_unlock(src_buf);
fallback:
	wlr_output_state_finish(&state);
	if (!return_buffer)
		wlr_scene_output_commit(m->scene_output, NULL);
	return NULL;
}
